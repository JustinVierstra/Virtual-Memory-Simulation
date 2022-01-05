#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <stdbool.h>

int pageTotal = 0;
int frameTotal = 0;
int requestTotal = 0;
int count = 0;
int pages[100];
int faults = 0;
bool check = true;
int currentFrame = 0;
int frameCount = 0;
int usedLast[100];
int leastRecentlyUsed = 0;
int referenceBit[100];
int placerHolder = 0;
int i = 0;
int y = 0;
int z = 0;
int j = 0;

int main(int argc, char *argv[]){
  void LRU();
  void CLOCK();
  void TEST();
  char *fileName;
  
  if (argc <= 2 || argc >= 4)
  {
        printf("Usage: proj4 input_file [LRU|CLOCK]\n");
        exit(1);
  }
  
  fileName = argv[1];
  
  FILE *in = fopen(argv[1], "r");
  if (!in)
  {
      printf("Can't open %s for reading\n", argv[1]);
      exit(1);
  }

  char line[100];
  while(fgets(line, 100, in) != NULL)
  {
      if(count == 0){
        sscanf(line, "%d %d %d", &pageTotal, &frameTotal, &requestTotal);
        count++;
      }else{
        sscanf(line, "%d", &pages[count]);
        count++;
      }
  }
  //printf("\nPageTotal: %d\nFrameTotal: %d\nrequestTotal: %d\n\n", pageTotal, frameTotal, requestTotal);

  if(strcmp(argv[2], "LRU")==0){
    LRU();
  }else if(strcmp(argv[2], "CLOCK")==0){
    CLOCK();
  }else{
      printf("%s must be [LRU|CLOCK]\n", argv[1]);
      exit(1);
  }
}

void LRU(){
  int frame[frameTotal];
  int usedLast[frameTotal];
  
  for(i=0; i<frameTotal;i++){
    usedLast[i]=-1;
  }

  frame[0] = pages[1];
  usedLast[0] = 0;
  faults++;
  currentFrame++;
  
  //printf("0> Page %d loaded into Frame %d\n", pages[1], 0);
  printf("Page %d loaded into Frame %d\n", pages[1], 0);

  for(i=2; i<requestTotal+1; i++){
    frameCount = 0;
    check = true;
    currentFrame%frameTotal;

    for(y=0; y<frameTotal;y++){
      if(i>0){
        //printf("%d> frame[%d]: %d\n",i-1, y, frame[y]);
      }
    }
    //for(y=0; y<frameTotal;y++){
    //  if(i>0){
    //    printf("%d> usedLast[%d]: %d\n",i-1, y, usedLast[y]);
    //  }
    //}

    do{
      if(frame[frameCount] == pages[i]){
        //printf("%d> Page %d already in Frame %d\n",i-1,pages[i], frameCount);
        printf("Page %d already in Frame %d\n", pages[i], frameCount);
        for(y=0; y<frameTotal;y++){
          if(usedLast[y]!=-1){
            usedLast[y]++;
          }
        }
        usedLast[frameCount] = 0;
        check = false;
        break;
      }
      frameCount++;
    }while(frameCount<frameTotal && check == true);


    if(check == true){
      if(usedLast[currentFrame]==-1){
        //printf("%d> Page %d loaded into Frame %d\n",i-1, pages[i], currentFrame);
        printf("Page %d loaded into Frame %d\n", pages[i], currentFrame);
        frame[currentFrame] = pages[i];
        for(y=0; y<frameTotal;y++){
          if(usedLast[y]!=-1){
            usedLast[y]++;
          }
        }
        usedLast[currentFrame] = 0;
        currentFrame++;
        faults++;
      }else{
        for(z=0; z<frameTotal;z++){
          usedLast[z]++;
          if(usedLast[z]>usedLast[leastRecentlyUsed] && usedLast[z] != -1){
            leastRecentlyUsed = z;
          }
        }

        //printf("%d> Page %d unloaded from Frame %d, Page %d loaded into Frame %d\n", i-1, frame[leastRecentlyUsed], leastRecentlyUsed, pages[i], leastRecentlyUsed);
        printf("Page %d unloaded from Frame %d, Page %d loaded into Frame %d\n", frame[leastRecentlyUsed], leastRecentlyUsed, pages[i], leastRecentlyUsed);
        currentFrame = leastRecentlyUsed;
        faults++;
        frame[leastRecentlyUsed]=pages[i];
        usedLast[leastRecentlyUsed%frameTotal] = 0;
      }
    }
  }

  //for(y=0; y<frameTotal;y++){
  //  printf("frame[%d]: %d\n",y, frame[y]);
  //}

  printf("%d page faults\n", faults);
}

void CLOCK(){
  int frame[frameTotal];
  int usedLast[frameTotal];

  for(i=0; i<frameTotal;i++){
    referenceBit[i]=-1;
  }

  frame[0] = pages[1];
  referenceBit[0] = 0;
  faults++;
  currentFrame++;
  
  //printf("0> Page %d loaded into Frame %d\n", pages[1], 0);
  printf("Page %d loaded into Frame %d\n", pages[1], 0);

  for(i=2; i<requestTotal+1; i++){
    frameCount = 0;
    check = true;
    currentFrame%=frameTotal;
    do{
      if(frame[frameCount] == pages[i]){
        //printf("%d> Page %d already in Frame %d\n",i-1,pages[i], frameCount);
        printf("Page %d already in Frame %d\n", pages[i], frameCount);
        if(referenceBit[frameCount]<1){
          referenceBit[frameCount]++;
        }
        check = false;
        break;
      }
      frameCount++;
    }while(frameCount<frameTotal && check == true);


    if(check == true){
      if(referenceBit[currentFrame]==-1){
        //printf("%d> Page %d loaded into Frame %d\n",i-1, pages[i], currentFrame);
        printf("Page %d loaded into Frame %d\n", pages[i], currentFrame);
        frame[currentFrame] = pages[i];
        referenceBit[currentFrame] = 0;
        currentFrame++;
        faults++;
      }else{
        for(j=currentFrame;j<currentFrame+frameTotal; j++){
          j%=frameTotal;
          if(referenceBit[j]==1){
            referenceBit[j]=0;
            currentFrame++;
          }else{
            currentFrame %= frameTotal;
            //printf("%d> Page %d unloaded from Frame %d, Page %d loaded into Frame %d\n", i-1, frame[currentFrame], currentFrame, pages[i], currentFrame);
            printf("Page %d unloaded from Frame %d, Page %d loaded into Frame %d\n", frame[currentFrame], currentFrame, pages[i], currentFrame);
            faults++;
            frame[currentFrame]=pages[i];
            currentFrame++;
            break;
          }
        }
      }
    }

    //for(y=0; y<frameTotal;y++){
    //  if(referenceBit[y]!=-1){
    //    printf("%d> frame[%d]: %d %d\n",i-1, y, frame[y], referenceBit[y]);
    //  }
    //}
  }
  //printf("\n");
  for(y=0; y<frameTotal;y++){
    printf("frame[%d]: %d %d\n",y, frame[y], referenceBit[y]);
  }
  //printf("\n");
  printf("%d page faults\n", faults);
}
