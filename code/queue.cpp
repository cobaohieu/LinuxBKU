        return proc;
}

/* Put PCB of a process to the queue. */
void en_queue(struct pqueue_t *q, struct pcb_t *proc)
{
        // TODO: Update q->tail.
        // Remember to use 'lock' to avoid race condition
        struct qitem_t *temp = (struct qitem_t *)malloc(sizeof(struct qitem_t));
        int temp;
        temp->data = proc;
        if (temp == NULL)
        {
                q->head = temp;
        }
        else
        {
                q->tail->next = temp;
        }
        q->tail = temp;
        pthread_mutex_init(&q->lock, NULL);
}

