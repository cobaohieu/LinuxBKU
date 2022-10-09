#include <vector>
#include <numeric>
#include <chrono>
#include <unistd.h>
#include <iomanip>
#include <sys/wait.h>
#include "EstimatePi.h"
#include "CommandLineHandler.h"
#include "Process.h"
#include <cstdint>

int main(int argc, char* argv[])
{
	const auto start = std::chrono::steady_clock::now();
	IntegerPair values{};
	double piValues{};
	double averagePi{};

	CommandLineHandler command(argc, argv); // Process commands and extract values

	if(command.isGoodParameters()){  // CommandLine values have been obtained
		 values = command.getValues();
		 int processes = values.first;
		 int iterations = values.second;

		 int wstatus;

		 // tell user what is happening..
		 std::cout << "Estimating pi " << processes << " processes with "
				   << iterations << " iterations for each process\n" << std::endl;

		 for(int i = 1; i <= processes; i++){
			pid_t cpid;
			double pi{};
			cpid = fork();
			if(cpid == -1){
				std::cerr << "Child creation unsuccessful" << std::endl;
			}
			if(cpid == 0){ /** Child process */
				EstimatePi estimate(iterations);
				pi = estimate.getPi();

				// Get this process and save the pid and pi values to file
				Process p(getpid(), pi);
				p.saveProcessToFile();

				// for debugging
				std::cout << "Process #" << i << " with pid: " << getpid()
						  << " estimated pi: " << std::setprecision(6)
						  << std::fixed<< pi << std::endl;

				piValues += pi;
				averagePi = piValues/i;
                exit(EXIT_SUCCESS);

			}else{ /** Parent process*/
				pid_t wId;
				do{
					wId = waitpid(cpid, &wstatus, WUNTRACED | WCONTINUED);
					if(wId == -1){
						std::cerr << "A problem occured " << std::endl;
					}

					if (WIFEXITED(wstatus)) {
						Process p;
						p.readProcessFromFile(cpid);
						std::cout << "Process " << cpid
								  << " terminated normally with return value "
								  << wstatus << " PI: " << std::setprecision(6)
								  << std::fixed << p.getPi() << std::endl;

						// delete the file
						std::remove(std::to_string(cpid).c_str());

					}else if(WIFSIGNALED(wstatus)){
						std::cerr << "Process " << cpid << " killed by signal"
								  << WTERMSIG(wstatus) << std::endl;
					}
					else if(WIFSTOPPED(wstatus)){
						std::cerr << "Process " << cpid << " stopped by signal"
								  << WSTOPSIG(wstatus)<< std::endl;
					}else if(WIFCONTINUED(wstatus)){
						std::cerr << "Process " << cpid << " continuing..."
								 << std::endl;
					}
				}while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));

				exit(EXIT_SUCCESS);
			}
		 }
		 const auto end = std::chrono::steady_clock::now();
		 const auto diff = end - start;
		 std::cout << "Average pi: " <<  std::setprecision(6) << std::fixed
				   << averagePi << std::endl;

		 std::cout << "\nCalculations took: " << std::setprecision(2)
				   <<(std::chrono::duration<double, std::milli>(diff).count())/1000
				  << " seconds" << std::endl;
	}// END OF GOOD COMMANDLINE STUFF
	/*Bad command line stuff should have been printed already if that is the
	   case since they are printed with std::cerr*/

	return 0;
}