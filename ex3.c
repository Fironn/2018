#include <stdio.h>                                                              
#include <stdlib.h>

typedef struct {                                                                
  int x;        /* アリの位置（横） */                                          
  int y;        /* アリの位置（縦） */                                          
  char dr;      /* 'R':右向き  'D':下向き */                                    
  int in;       /* 1:アリは盤上にいる 0:既に盤外に出ている */                   
}AntPos;

int main(int argc, char *argv[]){                                                                               
  int w, h, n;  /* 幅、高さ、初期状態でのアリの数 */                            
  int t=0;      /* 時間ステップのカウンタ */                                    
  int i, j, num;                                                                
  AntPos *ant;                                                                  
  FILE *ifile;

  if (argc < 2) {                                                               
    printf( "error: input file name is required!\n");                           
    exit(1);                                                                    
  }                                                                               
  ifile=fopen(argv[1],"r");                                                    
  if(ifile==NULL){                                                              
    printf("Cannot Open the file %s dasta!\n",argv[1]);                         
    exit(2);                                                                    
  }                                                                             
  /* ファイルオープン */                                                        
                                                                                
  fscanf(ifile,"%d%d%d",&w,&h,&n);                                              
  /* ファイルの1行目から盤の幅w、高さh、アリの数nを読み込む */                  
   
  ant=(int *)malloc(n*sizeof(AntPos));                
  /* アリの情報を収めておく構造体配列を動的に確保 */                            
                                                                                
  for(i=0;i<n;i++)fscanf(ifile,"%d%d %c",&ant[i].x,&ant[i].y,&ant[i].dr);    
  /* ファイルから各アリの位置と向きを読み込む。なお、文字型を読む時は           
     " %c"のように%c手前にスペースを入れると、R/D手前のスペースを読み飛ばせる。 
     読み込めたら、確認のため読んだ情報を一度出力しておこう */        
    for(i=0;i<n;i++){                               
        if(ant[i].x<=w||ant[i].x>=0||ant[i].y<=h||ant[i].y>=0){
            ant[i].in=1;
        }                                              
    }          
    for(i=0;i<n;i++)printf("%d %d %c\n",ant[i].x,ant[i].y,ant[i].dr);          
                                                                                
  /* 1ステップごとのループ。盤上にいるアリの数が0になったら終了 */              
  /* 時間の更新、アリの座標の更新、アリが盤の外に出たかどうかのチェックと表示、 
     
     2匹のアリが同じマスにいるかどうかのチェックと（必要なら）向きの更新 */     
    t=1;                                                        
    int test[100][100]={};        
    while(1){ 
        num=0;
        // printf("%d %d\n",num,n);
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){                                                           
                if(ant[i].in==1&&j!=i&&ant[j].x==ant[i].x&&ant[j].y==ant[i].y&&(ant[j].x+ant[j].y)%2==0){
                    if(ant[i].dr=='R')ant[i].dr='D';
                    else if(ant[i].dr=='D')ant[i].dr='R';
                    break;               
                }
            } 
            // printf("%d %d %d %c\n",i,ant[i].x,ant[i].y,ant[i].dr);
        }
        for(i=0;i<n;i++){                                                          
            if(ant[i].in==1){                                                         
                num++;
                if(ant[i].dr=='R')ant[i].x++;
                else if(ant[i].dr=='D')ant[i].y++;                       
                if(ant[i].x>w||ant[i].x<=0||ant[i].y>h||ant[i].y<=0){
                    printf("Step %d: Ant No.%d has gone out to (%d,%d).\n",t,i+1,ant[i].x,ant[i].y);
                    ant[i].in=0;
                }
                // printf("%d\n",num);
            }                                                                         
        }                                                                           
        if(num==0)break;    
        t++;                                                        
    }                                                                             
                                                                                
                                                                                
  return 0;                                                                     
}