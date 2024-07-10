#include <stdio.h>
#include <pthread.h>
pthread_mutex_t mutex;
balance = 10000;
void* deposit(void* arg){
	for (int i = 0;i<100;i++)
		balance+=(int)arg;
}
void* withdraw(void* arg){
	for(int i=0;i<100;i++)
		balance-=(int)arg;
}
int main(int arc,char** argv){
	int thread_no=1;
	if(argv >1)
		sscanf(strdup(argv[1]),"%d",&thread_no);
	fprint(stderr,"# of Deposit threads:%d\n ",thread_no);
	fprint(stderr,"#of withdraw threads:%d\n",thread_no);
	pthread_mutex_init(&mutex,NULL);
	pthread_t deposit_thread_id[thread_no];
	pthread_t withdraw_thread_id[thread_no];
	for (int i=0;i<thread_no;i++){
		pthread_create(&deposit_thread_id[i],NULL,deposit,(void*)100);
		pthread_create(&withdraw_thread_id[i],NULL,withdraw,(void*)100);
	}
	for (int i=0;i<thread_no;i++){
		pthread_join(deposit_thread_id[i],NULL);
		pthread_join(withdraw_thread_id[i],NULL);
	}
	pthread_mutex_destroy(&mutex);
	printf("final balance:%d.n",balance);
}
