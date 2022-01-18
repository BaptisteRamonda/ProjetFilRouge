#include <stdlib.h>
#include <stdio.h>
void execIndex(){
    FILE *fp;
    fp = popen("bash indexation_text.sh", "w");
    pclose(fp);
    
}
int main(){
    execIndex();
}