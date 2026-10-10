#include "common.h"
Train *load_trains(void){FILE*f=fopen(TRAIN_FILE,"r");Train *h=NULL,**tail=&h,*n; if(!f){f=fopen(TRAIN_FILE,"w");if(f){fprintf(f,"12627|Karnataka Express|Bengaluru|New Delhi|5\n12760|Charminar Express|Hyderabad|Chennai|5\n17015|Visakha Express|Bhubaneswar|Hyderabad|5\n");fclose(f);}f=fopen(TRAIN_FILE,"r");}if(!f)return NULL;while(1){n=calloc(1,sizeof *n);if(!n)break;if(fscanf(f,"%d|%63[^|]|%47[^|]|%47[^|]|%d\n",&n->number,n->name,n->source,n->destination,&n->total_seats)!=5){free(n);break;}*tail=n;tail=&n->next;}fclose(f);return h;}
void save_trains(Train*h){FILE*f=fopen(TRAIN_FILE,"w");if(!f){perror("Save trains");return;}for(;h;h=h->next)fprintf(f,"%d|%s|%s|%s|%d\n",h->number,h->name,h->source,h->destination,h->total_seats);fclose(f);}
void free_trains(Train*h){while(h){Train*n=h->next;free(h);h=n;}}
void show_trains(Train*h){puts("\nTRAIN NUMBER | TRAIN NAME | SOURCE -> DESTINATION | TOTAL SEATS");puts("----------------------------------------------------------------");if(!h)puts("No trains available.");for(;h;h=h->next)printf("%d | %s | %s -> %s | %d\n",h->number,h->name,h->source,h->destination,h->total_seats);}
int add_train(Train **head){Train *p,*n=calloc(1,sizeof *n);if(!n)return 0;n->number=read_int("Train number: ",1,999999);for(p=*head;p;p=p->next)if(p->number==n->number){puts("Duplicate train number.");free(n);return 0;}read_line("Train name: ",n->name,sizeof n->name);read_line("Source: ",n->source,sizeof n->source);read_line("Destination: ",n->destination,sizeof n->destination);if(!n->name[0]||!n->source[0]||!n->destination[0]||strchr(n->name,'|')||strchr(n->source,'|')||strchr(n->destination,'|')){puts("Fields must be non-empty and cannot contain '|'.");free(n);return 0;}for(p=*head;p;p=p->next)if(!strcmp(p->name,n->name)){puts("Duplicate train name.");free(n);return 0;}n->total_seats=read_int("Total seats: ",1,1000);if(!*head)*head=n;else{for(p=*head;p->next;p=p->next);p->next=n;}save_trains(*head);puts("Train added.");return 1;}


int delete_train(Train **head){
    if(!head || !*head){ puts("No trains available to delete."); return 0; }
    int number=read_int("Train number to delete: ",1,999999);
    Train **link=head;
    while(*link && (*link)->number!=number) link=&(*link)->next;
    if(!*link){ puts("Train number not found."); return 0; }
    /* Do not delete a train while any active booking references it. */
    Passenger *passengers=load_passengers();
    for(Passenger *x=passengers;x;x=x->next){
        if(x->train_number==number){
            puts("Cannot delete this train: active bookings exist. Cancel those tickets first.");
            free_passengers(passengers);
            return 0;
        }
    }
    free_passengers(passengers);
    Train *removed=*link;
    *link=removed->next;
    printf("Train %d (%s) deleted successfully.\n",removed->number,removed->name);
    free(removed);
    save_trains(*head);
    return 1;
}
