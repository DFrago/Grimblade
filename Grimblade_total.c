#include <stdio.h>
#include <math.h>
#include <string.h>
#define max_input 100
/*All used for data type error correction (used in stat allocation) */
char value[max_input]="",str[max_input]="";
double temp,val=1e-12;
int ne,pass=0,dead_sarah,dead_addict;
/*******************************************/
/*Variables for skipping over portions of functions upon return from another function. */
int return_home();
int dead_rat=1;
int no_reset=1,savecheck=1,initialcheck=1;
/******************************/
/*For combat */	
char enemy_name[10][30]={{"smol rat"},{"sarah"},{"addict"}};
int enemy_attack,enemy_strength, enemy_defense,enemy_magic,enemy_range,enemy_health;
int enemies[10][6]={{4,3,3,0,0,20},{5,7,2,0,0,35},{10,10,10,0,0,30}};
/***************************/
/*Functions*/
char locate(),back(),error_correction();
double action();
int fight(),grimblade(),map(),inventory(),help(),death(),combat(),killcount(),dusty_cave(),lumdoozle(),edible(),back_combat(),character(),recover(),bofaland();
/***************************/
/*Global Variables*/
char food_name[10][30]={{"cheese"},{"bofa"}},items[5][30]={{"scuffed shirt"},{"scuffed pants"},{"bronze dagger"},{"leather pants"},{"leather shirt"}},name[30];;
double n,s,e,w,attack,strength,range,magic,defense;
/*For the varialbe 'food' the first number represents wether or not it has been found, and the second determines how many hp it restores */ 
int food[10][2]={{0,5},{0,10}},locations[10][4]={{0,0,0,0},{5,0,0,0},{7,0,0,10}},item_status[10]={1,1,1,1,1,1,1,1,1,1};
int combat_boi,ih=1, no_health=1,peppega=0,noob=1,ch_health=0,bing_bongs=30,eating_timer=1,killswitch=1,kills,admin=1;
/*item status is used to tell if that item has already been equipped. 2 means it has been equipped, 1 means that it is not equipped.NEEDS TO BE GLOBAL */
/*The order for item bonus is attack,defense,strength,then magic */
int itemcheck[20],yo=1,attack_bonus=0,defense_bonus=0,strength_bonus=0,magic_bonus=0,speed=0,range_bonus=0,og_health;

int main (void){
int name_err=1,i,deez=1,y=0;
char exit_check[5],input [30],playthrough[30];
/*Items*/
/*0 = scuffed shirt, 1=scuffed pants, 3=bronze dagger 4=leather pants 5=leather shirt */
itemcheck[0]=2; /* scuffed shirt*/
itemcheck[1]=2; /*scuffed pants*/
/****************/                                                                                         
	if(initialcheck!=2){
		recover(7);
		initialcheck=1;
	}
	if(savecheck==2){
		printf("\nYou have a recent save. Continue from last save or start a new playthrough? [continue/new]\n");
		scanf("%s",&playthrough);
			if(strcmp(playthrough,"new")==0){
				savecheck=1;
				main();
			}
			else if(strcmp(playthrough,"continue")==0){
				printf("\nLooks like %s gets to live another day\n",name);
				savecheck=1;
				recover(1);
			}
			else{
				printf("\nUnrecognized command\n");
				back("exit");
			}
	}
	if(kills==1 || kills==3 || kills==6 || kills==10){
		if(killswitch==1){
		killcount(0);
	    }
	}
	if(ch_health==0 && ih==2){
		death();
	}
	while(deez==1){
		if(noob==1){
		printf("\nEnter 'start' to begin the great adventure\n");
     	}
	scanf("%s",&input);
		if (strcmp(input,"start")==0 && noob==1){
			noob=2;
			grimblade();
		}		
		if(strcmp(input,"exit")==0){
			printf("\n\nYou are already on the main page, pressing exit now will close Grimblade. Are you sure [yes or no]\n");
			scanf("%s",&exit_check);
			if(strcmp(exit_check,"no")==0){
				back("exit");
			}
			else if(strcmp(exit_check,"yes")==0){
        		printf("\nDo you want to save? [yes/no]\n");
        		scanf("%s",&playthrough);
        			if(strcmp(playthrough,"yes")==0){
        				printf("..........Saving............");
        				save(3);
					}
					else if(strcmp(playthrough,"no")==0){
						exit(0);
						return 0;	
					}
			}
			else{
			error_correction("leaving");
			}
		}
   		else if(strcmp(input,"inventory")==0){
   			inventory(input);
		}
		else if(strcmp(input,"move")==0) {
			yo=1;
			action(input);
		}
    	else if(strcmp(input,name)==0){
    		character(input);	
			}
    	else if(strcmp(input,"help")==0){
   			help("help");
		}
		else if(strcmp(input,"map")==0){
			map("bofa");
			}
		else if(strcmp(input,"eat")==0){
			eating_timer=1;
			edible(500);
		}
		else if(strcmp(input,"save")==0){
			printf("\n............Saving............\n");
			save(2);
		}
		else{
    		error_correction("main");
		}
    

	}		

return 0;
}

double action(char move[10]){
char mov[30];
int i=0, y=0,med=1;
/***************************/
printf("\nYou can currently move %d space(s)\n",speed);
	for(i==0;i<speed;i++){
		for(y==0;y<=10;y++){
			if(n==locations[y][0] && e==locations[y][1] && s==locations[y][2] && w==locations[y][3]){
				locate(y);
			} 
		}
		scanf("%s",& mov);
		if(strcmp(mov,"w")==0){
	 		n++;
	 		printf("\nMoved north one space\n");	 
		}
		else if(strcmp(mov,"s")==0){
			s++;
			printf("\nMoved south one space\n");
		}
		else if(strcmp(mov,"d")==0){
			e++;
			printf("\nMoved east one space\n");
		}
		else if(strcmp(mov,"a")==0){
			w++;
			printf("\nMoved west one space\n");
		}
		else if(strcmp(mov,"stop")==0){
    		back("exit");
		}
		else if(strcmp(mov,"exit")==0){
			yo=2;
			back("exit");
		}
		else{
    		error_correction("movement");
		}
	}
printf("\n\nYour movements have left you here n: %lf  e: %lf  s: %lf w: %lf \n",n,e,s,w);
}

int inventory(char user[10]){
/* \\I is used in the for loop which increments itemcheck, and X is for incrementing the array spot, y is for incrementing the for loop used in inventory command */
char inventory_command[30],item_command[30];
/* order for bonuses is attack, strength, defense, magic, range */
int item_bonus[5][5]={{0,1,0,0,},{0,2,0,0,},{5,0,0,0},{0,5,0,0},{0,5,0,0,0}};
int i=0,x=0,y=0;
/***************************/
printf("\n\nInventory:\n");
	for(i==0;i<=9;i++){
		if(itemcheck[x]==2){	
			printf("\n%s\n",items[x]);
		}
		x++;
	}	
	scanf("%s",inventory_command);	
	if(strcmp(user,"combat")==0){
		if(strcmp(inventory_command,"exit")==0){
	  		combat(combat_boi);
		}
	}
	back (inventory_command);
	/*fruit[strlen(fruit)-1]='\0'; */
	if(strcmp(inventory_command,"equip")==0){
		printf("\nname of item that you wish to equip: ");
		fflush(stdin);
		fgets(item_command,30,stdin);
       	item_command[strlen(item_command)-1]='\0';
		for(y==0;y<=9;y++){
			if(strcmp(item_command,items[y])==0){	
				if(item_status[y]==2){
			 		printf("\n%s is already equipped\n",items[y]);
					if(strcmp(user,"combat")==0){
	  		    		inventory("combat");
	        		}
			 		inventory("inventory");
				}	
				else {
		    		item_status[y]=2;
					printf("\nEquipped %s\n",items[y]);
					attack_bonus=attack_bonus+item_bonus[y][0];
					defense_bonus=defense_bonus+item_bonus[y][1];
					strength_bonus=strength_bonus+item_bonus[y][2];
					magic_bonus=magic_bonus+item_bonus[y][3];
					range_bonus=range_bonus+item_bonus[y][4];
					if(strcmp(user,"combat")==0){
	  					inventory("combat");
	  				}	
				inventory("inventory");
		        }
    		}	
		}
	}
	else if(strcmp(inventory_command,"remove")==0){
		printf("\nname of item that you wish to remove: ");
		fflush(stdin);
		fgets(item_command,30,stdin);
		item_command[strlen(item_command)-1]='\0';
			for(y==0;y<=9;y++){	
				if(strcmp(item_command,items[y])==0){	
					if(item_status[y]==1){
						printf("\n%s is not equipped\n",items[y]);
						if(strcmp(user,"combat")==0){
	  		        		inventory("combat");
	                	}
					inventory("inventory");
				    }	
					else{
						item_status[y]=1;
						printf("\nRemoved %s\n",items[y]);
						attack_bonus=attack_bonus-item_bonus[y][0];
						defense_bonus=defense_bonus-item_bonus[y][1];
						strength_bonus=strength_bonus-item_bonus[y][2];
						magic_bonus=magic_bonus-item_bonus[y][3];
						range_bonus=range_bonus-item_bonus[y][4];
	            		if(strcmp(user,"combat")==0){
	  		        		inventory("combat");
	                    }
					inventory("inventory");
					}
				}
        	}
	}
	else{
		if(strcmp(user,"combat")==0){
		error_correction("inventory/combat"); 
	  	}
	error_correction("inventory");
	}
	if(strcmp(user,"combat")==0){
		inventory("combat");  
	}
	inventory("inventory");
}

char back(char leave[]){
	if(strcmp(leave,"exit")==0){
		printf("\n\nYou are now on the main page\n");
		main();
	}
	else if(strcmp(leave,"recover")==0){
		main();
	}
}

int character(char name_para[30]){
int y=0;
/********************************/
printf("\nEquipped items:\n");
	for(y==0;y<=9;y++){
		if(item_status[y]==2){
			printf("\n%s\n",items[y]);
		}			
	}
	printf("\nHealth: %d\n",(int)ch_health);
	printf("\nBing Bongs: %d\n",bing_bongs);
	printf("\nCurrent item bonuses:\n");
	printf("\nAttack bonus: %d\n",attack_bonus);
	printf("\nStrength bonus: %d\n",strength_bonus);
	printf("\nDefense bonus: %d\n",defense_bonus);
	printf("\nMagic bonus: %d\n",magic_bonus);
	printf("\nRange bonus: %d",range_bonus);
    printf("\n\nCurrent stats:\n");
    printf("\nAttack: %d",(int)attack);
    printf("\nStrength: %d",(int)strength);
	printf("\nDefense: %d",(int)defense);
	printf("\nMagic: %d",(int)magic);
	printf("\nSpeed: %d\n",(int)speed);
	if(strcmp(name_para,"combat")==0){
		combat(combat_boi);
	}
	else{

	back("exit");
	}
}

char error_correction(char where[15]){
int deez=1;
/************************************/
printf("\nUnrecognized command\n");
peppega++;
	if(peppega==3){
		printf("\nEnter 'help' at the main menu if you need some some knowledge about the commands.\nTyping exit will bring you to the main menu\n");
		peppega=0;
	}	
    if(strcmp(where,"main")==0){
			main();
	}	
    if(strcmp(where,"inventory")==0){
           inventory("inventory");
	}
	if(strcmp(where,"inventory/combat")==0){
   		inventory("combat");
	}
    if(strcmp(where,"movement")==0){
   		action("move");
	}
	if(strcmp(where,"kills")==0){
   		killcount(0);
	}
	if(strcmp(where,"leaving")==0){
		printf("\nYou just had to enter in yes or no. You've been brought back to the main menu.\n");
		main();   	   	
	}
	if(strcmp(where,"equipy")==0){
		printf("\nItem is not in inventory\n");
		inventory("inventory");
	}
}

int grimblade (){
char logik[4],input [30];
char  build;
double totalsp,extrasp,skillapply =0;
int a,s,d,r,m,loop=1,name_err=1,i,deez =1,bofa=1;
/*****************/
/*Initial stat management */
	if(no_health==1){
		while(name_err==1){
			printf("Greetings traveler, what shall I call you?  ");
			scanf("%s",&name);
			printf("\n\n\nSo you're telling me that your name is %s ?",name);
			printf("\n\n(Type yes or no then enter)\n");
			scanf("%s",&logik);
				if(strcmp(logik,"yes")==0){
					name_err=2;
					printf("\nYou have a total of 70 skill points to distribute as you please.");
					printf("\nThe categories are:")	;
					printf("\nAttack (effects accuracy of attacks)");
					printf("\nStrength (effects your max melee hit)");
					printf("\nDefence (determines how much damage you take from incoming attacks.)");
					printf("\nRange (contributes to the effectiveness of ranged attacks)");
					printf("\nMagic (contributes to the effectiveness of magic attacks. )");	
					printf("\nSpeed (dictates how many spaces you can move. )");	
					printf("\nHealth (How much damage you can take before you die.)");
					printf("\nYou need at least one point in health.");
				}
				else{
    				printf("\nSorry I have short term memory loss, let us try again.\n\n");
				}

		}

	}
		while(totalsp <70){ 
    		while(loop==1){	
				printf("\n\nHow many points into Attack?");
				fflush(stdin);
				fgets(value,100,stdin);   
        			if(sscanf(value,"%lf",&temp)==1){
						ne=(int)temp;
						if(fabs(temp-ne)/temp>val){
		    			}
						else{
							pass=1;
							skillapply=ne;
						}
					}
					else if(sscanf(value,"%s",str)==1){
						pass=2;
					}
					else{
						printf("Input not recognized\n");
					}
					if(pass==1){
						attack= attack + skillapply;  
						skillapply = 0; 
						loop=1;
						break;
					}   
			}
    	while(loop==1){
			printf("\n\nHow many points into Strength?");
			fflush(stdin);
			fgets(value,100,stdin);   
        		if(sscanf(value,"%lf",&temp)==1){
					ne=(int)temp;
		    		if(fabs(temp-ne)/temp>val){
		    	}
		  		else{
					pass=1;
					skillapply=ne;	
				}	
				}
				else if(sscanf(value,"%s",str)==1){
					pass=2;
				}
				else{
					printf("Input not recognized\n");
				}
				if(pass==1){
					strength= strength + skillapply;  
					skillapply = 0; 
					loop=1;
					break;
				}
		}
		while(loop==1){	
			printf("\n\nHow many points into Defense?");
			fflush(stdin);
			fgets(value,100,stdin);   
    			if(sscanf(value,"%lf",&temp)==1){
			ne=(int)temp;
			if(fabs(temp-ne)/temp>val){
			}
			else{
			pass=1;
			skillapply=ne;
			}
		}
		else if(sscanf(value,"%s",str)==1){
			pass=2;
		}
		else{
			printf("Input not recognized\n");
		}
		if(pass==1){
			defense= defense + skillapply;  
			skillapply = 0; 
			loop=1;
			break;
		}
		}
		while(loop==1){
		printf("\n\nHow many points into Range?");
		fflush(stdin);
		fgets(value,100,stdin);   
    		if(sscanf(value,"%lf",&temp)==1){
				ne=(int)temp;
					if(fabs(temp-ne)/temp>val){
					}
					else{
					pass=1;
					skillapply=ne;
					}
			}
			else if(sscanf(value,"%s",str)==1){
				pass=2;
			}
			else{
				printf("Input not recognized\n");
			}
			if(pass==1){
				range= range + skillapply;  
				skillapply = 0; 
				loop=1;
				break;
			}    
		}


		while(loop==1){
			printf("\n\nHow many points into Magic?");
			fflush(stdin);
			fgets(value,100,stdin);   
    			if(sscanf(value,"%lf",&temp)==1){
				ne=(int)temp;
					if(fabs(temp-ne)/temp>val){
		    		}
					else{
						pass=1;
						skillapply=ne;
					}
				}
				else if(sscanf(value,"%s",str)==1){
					pass=2;
				}
				else{
					printf("Input not recognized\n");
				}
				if(pass==1){
					magic= magic + skillapply;  
					skillapply = 0; 
					loop=1;
					break;
				}
	    
		}
	

		while(loop==1){
			printf("\n\nHow many points into Speed?");
			fflush(stdin);
			fgets(value,100,stdin);   
				if(sscanf(value,"%lf",&temp)==1){
					ne=(int)temp;
						if(fabs(temp-ne)/temp>val){
		    			}
		  				else{
							pass=1;
							skillapply=ne;
						}
				}
				else if(sscanf(value,"%s",str)==1){
					pass=2;
				}
				else{
					printf("Input not recognized\n");
				}
				if(pass==1){
				speed= speed + skillapply;  
				skillapply = 0; 
				loop=1;
				break;
				}	    
		}

		while(loop==1){
			printf("\n\nHow many points into Health?");
			fflush(stdin);
			fgets(value,100,stdin);   
    		if(sscanf(value,"%lf",&temp)==1){
				ne=(int)temp;
		    		if(fabs(temp-ne)/temp>val){
		    		}
		  			else{
						pass=1;
						skillapply=ne;		
					}	
			}
			else if(sscanf(value,"%s",str)==1){
				pass=2;
			}
			else{
				printf("Input not recognized\n");
			}
			if(pass==1){
				ch_health= ch_health + skillapply;  
				skillapply = 0; 
				og_health=ch_health;
				loop=2;
			}
		}
		totalsp=ch_health+speed+attack+strength+defense+range+magic;
			if(totalsp > 70){
  				loop=1;
				printf("\nYou have applied more than 70 skill points. All points will be erased.");
  				totalsp=0;
  				attack=0;
  				strength=0;
  				defense=0;
  				range=0;
  				magic=0;
  				speed=0;
  				ch_health=0; 	
 			}
			if(totalsp<70){
				loop=1;
				extrasp= 70.0 - totalsp;
				printf("\nYou have %d points left, cycle through again and apply them.",(int)extrasp);
    			printf("\n\nThese are your current stats:");
    			printf("\nAttack: %d",(int)attack);
    			printf("\nStrength: %d",(int)strength);
   				printf("\nDefence: %d",(int)defense);
    			printf("\nRange: %d",(int)range);
    			printf("\nMagic: %d",(int)magic);
    			printf("\nSpeed: %d",speed);
    			printf("\nHealth: %d",ch_health);
			}	
		}			
	if(totalsp ==70){
			printf("\nYou have assigned all skill points, your skills are shown below");
   			printf("\n\nThese are your current stats:");
    		printf("\nAttack: %d",(int)attack);
    		printf("\nStrength: %d",(int)strength);
   			printf("\nDefence: %d",(int)defense);
    		printf("\nRange: %d",(int)range);
    		printf("\nMagic: %d",(int)magic);	
    		printf("\nSpeed: %d",speed);	
   		 	printf("\nHealth: %d",ch_health);	
	}	
	if(ch_health>=1){
		ih=2;
	}
	else{
		printf("\nYou forgot to assign at least one point into health. All points will be erased.");
		loop=1;
  		totalsp=0;
  		attack=0;
  		strength=0;
  		defense=0;
  		range=0;
  		magic=0;
  		speed=0;
  		ch_health=0;
	    no_health=2;
		grimblade();
	}
	printf("\n\nSo the journey begins!\n");
	printf("\nEnter help if you want the tutorial\n\n");
    noob=2;
    locate(0);
	back("exit");
}
/*********************************************************************/
int help(char assistance[10]){
	if(strcmp(assistance,"help")==0){
		/*exit,inventory,move,your characters name,help */
		FILE*fp;
    	char buf[1000];
		fp=fopen("tutorial.txt","r");
			if(!fp){
				return 1;
			}
			while(fgets(buf,1000,fp)!=NULL){
			printf("%s",buf);
			}
			fclose(fp);
			back("exit");
	}
}
int map(char test[10]){
int i=0;
	if(strcmp(test,"bofa")==0){
		printf("\n\nCurrent location n: %lf  e: %lf  s: %lf w: %lf \n",n,e,s,w);
		printf("\nDusty cave: %d: %d: %d: %d\n",locations[0][0],locations[0][1],locations[0][2],locations[0][3]);
	    printf("\nLumdoozle %d: %d: %d: %d:\n",locations[1][0],locations[1][1],locations[1][2],locations[1][3]);
	    printf("\nWeston pits %d: %d: %d: %d:\n",locations[2][0],locations[2][1],locations[2][2],locations[2][3]);
	    printf("\n");
	}
	back("exit");
}

char locate(int local_test){	
	if(local_test==0){
		dusty_cave(local_test);
	}
	else if (local_test==1){
		lumdoozle(local_test);
	}
	else if(local_test==2){
		weston(local_test);
	}
	else if(local_test==3){
		bofaland(local_test);
	}
}

int dusty_cave(int bofa){
	FILE*dusty_pointer;
	char buffer[1000];
	dusty_pointer=fopen("dusty_cave.txt","r");
		if(!dusty_pointer){
		return 1;
		}
		while(fgets(buffer,1000,dusty_pointer)!=NULL){
		printf("%s",buffer);
		}
		fclose(dusty_pointer);
		n++;
		back("exit");
}

int lumdoozle(int bofa){
FILE*lumdoozle_pointer;
FILE*lp;
int y=0,x=0,combat_status,z=0;
char buf[1000],input[20],fight[10];
/**********************/	
	if(dead_sarah!=2){
	if(dead_rat==1){
		lumdoozle_pointer=fopen("lumdoozle.txt","r");
			if(!lumdoozle_pointer){
			return 1;
			}
			while(fgets(buf,1000,lumdoozle_pointer)!=NULL){
				printf("%s",buf);
			}
			fclose(lumdoozle_pointer);
			while(y==0){
			scanf("%s",& input);
			if(strcmp(input,"yes")==0){
				printf("\nbronze dagger added to inventory\n");
				itemcheck[2]=2;/*bronze dagger */
				y=1;
			}
			else if(strcmp(input,"no")==0){
			printf("\nlmao you bitch");
			y=1;
			}
			else{
				printf("\nUnreconginzed command\n");
			}
	}
	printf("\nAs you walk on you see a lil rat muching on some cheese\n");
	printf("\nSeems like we have a problem here because the rat seems to be enjoying his food but you are hungry and know cheese slaps\n");
	printf("\nFight the rat? [yes/no]\n");
		while(x==0){
		scanf("%s",& fight);
		if(strcmp(fight,"yes")==0){
			x=1;
			combat(0);
		}
	    else if(strcmp(fight,"no")==0){
	    	printf("\nYou decide that it's easier to fight the hunger than the rat so you keep on moving");
	    	x=1;	
		}
		else{
			printf("\nUnreconginzed command\n");
		}
    }
  /*dead rat */  
	}
	lp=fopen("lump.txt","r");
		if(!lp){
		return 1;
		}
		while(fgets(buf,1000,lp)!=NULL){
			printf("%s",buf);
		}
	combat(1);
	fclose(lp);
	}
	printf("\nYou have left lumdoozle");
	n++;
	back("exit");
}

int weston(int bofa){
int check=1,loop=1;
char input[10];
FILE*weston;
FILE*weston_burn;
char buf[1000];
if(dead_addict!=2){
weston=fopen("weston.txt","r");
	if(!weston){
	return 1;
	}
	while(fgets(buf,1000,weston)!=NULL){
		printf("%s",buf);
	}
	while(loop==1){
	scanf("%s",input);
		if(strcmp(input,"yes")==0){
				printf("\nYou hand the strange man 10 bing-bongs");
				printf("\nHe slowly smiles and opens the gate for you.");
				check=2;
				bing_bongs-=10;
				loop=2;
		}
		else if(strcmp(input,"no")==0){
			printf("\nYour desire to save money overcomes your desire to explore.");
			printf("\nYou turn away and the man at the gate lights up his cigarette and gives you a cold stare as you leave.");
			loop=2;
			back("exit");
		}
		else{
			printf("\nUnrecognized command\n");
		}
	}
	if(check==2){
		weston_burn=fopen("weston_burn.txt","r");
			if(!weston_burn){
			return 1;
			}
			while(fgets(buf,1000,weston_burn)!=NULL){
			printf("%s",buf);
			}
			scanf("%s",input);
				if(strcmp(input,"no")==0){
					printf("\nYou don't want no trouble so you politely decline the addicts offer");
				}
				else if(strcmp(input,"yes")==0){
					if(bing_bongs<100){
						printf("\nThat's not enough bud. You trying to scam me?!?!?!");
						printf("\nThe addict gets offended and attacks you");
						combat(2);
					}
					else if (bing_bongs>=100){
						printf("\nNice doing business with you.");
						printf("\n-100 bing bongs");
						printf("\nDeez added to inventory");
					}
				}
				else if(strcmp(input,"attack")==0){
					printf("\n'Are you fu....'");
					printf("\nYou attack the addict");
					combat(2);
				}
			}
	}		 /*Dead addict */
	printf("\nYou leave the weston burn pits");
	back("exit");			
}

int killcount(int kills){
char input[20];
printf("\nYou have earned a skill point. Choose a skill to increase. \n(attack,strength,defense,magic,range,speed)\n");
scanf("%s",input);	
	if(strcmp(input,"attack")==0){
		attack++;
		printf("\nOne point added to attack");
		killswitch=2;
		back("exit");
	}
	else if(strcmp(input,"strength")==0){
		strength++;
		printf("\nOne point added to strength");
		killswitch=2;
		back("exit");
	}
	else if(strcmp(input,"defense")==0){
		defense++;
		printf("\nOne point added to defense");
		killswitch=2;
		back("exit");
	}
	else if(strcmp(input,"magic")==0){
		magic++;
		printf("\nOne point added to magic");
		killswitch=2;
		back("exit");
	}
	else if(strcmp(input,"range")==0){
		range++;
		printf("\nOne point added to range");
		killswitch=2;
		back("exit");
	}
	else if(strcmp(input,"speed")==0){
		speed++;
		printf("\nOne point added to speed");
		killswitch=2;
		back("exit");
	}
	else{
		error_correction("kills");
	}	
}

int combat(int who){
/*This list refers to the number that is passed to 'who' in order to ID the enemy. It will always be one highter than the number position
of that enemy within enemy_name */
/*If 'who' comes in as 300, that means that it's being passed from a interface, so it will skip the intro. */
/*smol rat=1  */
int y,timer=1,eating_status;
char input[30];
/*****************/
	if(ch_health==0){
		death();
	}
	y=who;
	combat_boi=y;
	enemy_attack=enemies[y][0];
	enemy_strength=enemies[y][1];
	enemy_defense=enemies[y][2];
	enemy_magic=enemies[y][3];
	enemy_range=enemies[y][4];
	if(no_reset==1){
	enemy_health=enemies[y][5];
	}
	printf("\nYou are in combat with %s\n",&enemy_name[y]);
	while(timer=1){
		fflush(stdin);
		fgets(input,30,stdin);
		input[strlen(input)-1]='\0';
	if(strcmp(input,enemy_name[y])==0){
		printf("%s's stats:\n",enemy_name[y]);
		printf("\nattack: %d",enemies[y][0]);
		printf("\ndefense: %d",enemies[y][1]);
		printf("\nstrength: %d",enemies[y][2]);
		printf("\nmagic: %d",enemies[y][3]);
		printf("\nrange: %d",enemies[y][4]);
		printf("\nhealth: %d",enemies[y][5]);					  
	} 
	else if(strcmp(input,"eat")==0){
		eating_timer=1;
		edible(y);
    }
	else if(strcmp(input,"inventory")==0){
		combat_boi=y;
		inventory("combat");
	}
	else if(strcmp(input,name)==0){
		combat_boi=y;
		character("combat");	
	}
	else if(strcmp(input,"attack")==0){
		fight(who);
	}
	combat(who);
    }

}

int edible(int restore){
int	y=0,x=0,eating_status=1;
char i_eat[30];
/***********************/
printf("\nFood that you currently have:\n");
	for(y==0;y<=10;y++){
		if(food[y][0]==1){
		printf("\n%s:   restores %d health\n",food_name[y],food[y][1]);
        } 
	} 
	printf("\neat: ");
	while(eating_timer=1){
		y=0;
		for(y==0;y<=10;y++){
			fflush(stdin);
			fgets(i_eat,30,stdin);
			i_eat[strlen(i_eat)-1]='\0';
			if(strcmp(i_eat,food_name[y])==0){
				printf("\nYou ate %s and restored %d health",food_name[y],food[y][1]);
				ch_health+=food[y][1];
				food[y][0]=0;
				if(restore==500){
					back("exit");
				}
				else{
					eating_timer=2;
					combat(restore);
				}
			}	 
			else if(strcmp(i_eat,"exit")==0){
    			if(restore==500){
      			back("exit");
				}
				else{
					eating_timer=2;
					combat(restore);
				}		
			}
	  		else{
      			printf("\nUnrecognized command\n");
      			if(restore==500){
      			edible(500);
		  	}
		  	else{
		  		edible(restore);
		  		eating_timer=1;
		  	}
			}
		}
	}
	if(restore==500){
		back("exit");
	}
	
	
}

int death(int reaper){
char input[30];
int deez=1;
FILE*respawn;
/********************/
	while(deez==1){
		printf("\n\nRIP. You dead.\n[respawn/exit]\n");
		scanf("%s",input);
			if(strcmp(input,"respawn")==0){
				deez=2;
				ch_health=og_health/2;
				n=1;e=0;s=0;w=0;
				printf("\nYou have been brought back to N:0 E:0 S:0 W:0\n");
				printf("\nYour health is also half of your max value\n");				
				back("exit");	
			}
			else if(strcmp(input,"exit")==0){
				deez=2;
				save(1);
				printf("\n............Saving............\n");
				exit(0);
			}
			else{
				printf("\nUnrecognized command");
			}
	}	
}

/*Chungus will hold the 'y' value from combat, which serves as the identifier for the enemy */
/*no_reset stops enemy_health from being redefined everytime you go back to the combat function */
/* loop and boi are both used for looping the damage calculators. loop is for the player, boi is for the enemy. */
/* 'f_stat' variables are the sum of the players stats and current item bonuses. These are used in the calculations to determine how much damage the player will deal and recieve */
int fight(int chungus){
int damage,enemy_damage,prng,erng,loop=1,boi=1,fstrength,fdefense,fattack,half_def;
loop=1;
boi=1;
half_def=defense/2;
fstrength=strength+strength_bonus;
fattack=attack+attack_bonus;
fdefense=defense+defense_bonus;
	while(loop==1){ 
	prng=rand() % (fstrength+1-0)+0;
	damage=prng-enemy_defense;
		if(prng==0){
			if(fattack>=5 && fattack<10){
			fight(chungus);	
			}
				if(fattack>=10 && fattack <20){
					if(damage<1){
						fight(chungus);
					}
				}
					if(fattack>=25 && fattack<30){
						if(damage<2){
							fight(chungus);
						}
					}
				if(fattack>=35 && fattack<45){
					if(damage<3){
						fight(chungus);
					}
				}
				if(fattack>=45 && fattack <55){
					if(damage<4){
						fight(chungus);
					}
				}
				if(fattack>=55 && fattack<69){
					if(damage<5){
						fight(chungus);
					}
				}
				if(fattack>=69){
					if(damage<6){
						fight(chungus);
					}
				}			
		}
	loop=2;	
	}
	while(boi==1){ 
	erng=rand() % (enemy_strength+1-0)+0;
	enemy_damage=erng-half_def;
		if(erng==0){
			if(enemy_attack>=5 && enemy_attack<10){
			fight(chungus);	
			}
				if(enemy_attack>=10 && enemy_attack <20){
					if(enemy_damage<1){
						fight(chungus);
					}
				}
					if(enemy_attack>=25 && enemy_attack<30){
						if(enemy_damage<2){
							fight(chungus);
						}
					}
				if(enemy_attack>=35 && enemy_attack<45){
					if(enemy_damage<3){
						fight(chungus);
					}
				}
				if(enemy_attack>=45 && enemy_attack <55){
					if(enemy_damage<4){
						fight(chungus);
					}
				}
				if(enemy_attack>=55 && enemy_attack<69){
					if(enemy_damage<5){
						fight(chungus);
					}
				}
				if(enemy_attack>=69){
					if(enemy_damage<6){
						fight(chungus);
					}
				}			
		}
	boi=2;	
	}
	if(damage>0){
		printf("\nYou attack %s",enemy_name[chungus]);
		printf("\nYou deal %d damage",damage);
    	enemy_health=enemy_health-damage;
		printf("\n%s has %d health left",enemy_name[chungus],enemy_health);
		printf("\n.............................\n");
			if(enemy_health<=0){
				printf("\nYou killed %s",enemy_name[chungus]);	
				kills++;
				killswitch=1;
				no_reset=1;
				return_home(enemy_name[chungus]);
			}
    }
    else if(damage<=0){
    	printf("\nYou attack %s, but you miss.",enemy_name[chungus]);
    	printf("\n%s has %d health left",enemy_name[chungus],enemy_health);
    	printf("\n.............................\n");
	}
	if(enemy_health>0){
		printf("\n.............................\n");
		printf("\n%s attacks you.",enemy_name[chungus]);
		if(enemy_damage>0){
    		printf("\n%s does %d damage",enemy_name[chungus],enemy_damage);
    		ch_health=ch_health-enemy_damage;
   			printf("\nYou have %d health",ch_health);
    		printf("\n.............................\n");
		}
		else if(enemy_damage<=0){
			printf("\n%s missed.",enemy_name[chungus]);
			printf("\nYou have %d health",ch_health);
			printf("\n.............................\n");
		}
   }
   if(ch_health<=0){
		no_reset=1;
		death(0);
	}
no_reset=2;
}

int return_home(char who[30]){
int loop=1;
	char input[30];
	if(strcmp(who,"smol rat")==0){
		dead_rat=2;
		printf("\nCheese added to inventory\n");
		food[0][0]=1;
		lumdoozle(1);
	}
	if(strcmp(who,"sarah")==0){
		printf("\nShe was pretty. You hate to see it.");
		printf("\nAfter that encounter you decide that you've had enough of this town and decide to leave");
		dead_sarah=2;
		lumdoozle(2);
	}
	if(strcmp(who,"addict")==0){
		printf("\nLeather pants added to inventory");
		printf("\nleather shirt added to inventory");
		itemcheck[3]=2;
		itemcheck[4]=2;
        printf("\nYou find one strange capsule on the ground labeled 'deez'");
        printf("\nEat the Deez? [yes/no]");
        	while(loop==1){
			scanf("%s",&input);
				if(strcmp(input,"yes")==0){
        			printf("\nFather forgive me for the gainz I am about to recieve.");
					printf("You eat the Deez and gain 5 strength levels.");
					strength=strength+5;
					printf("\nTastes like chicken.");
					loop=2;	
				}
				else if(strcmp(input,"no")==0){
					printf("\nYou decide not to take the gainz and continue on.");
					loop=2;
				}
				else{
				printf("\nUnrecognized command\n");	
				}
			}
		dead_addict=2;
		weston(0);
	}
}

int save(int num){
int y=0;
FILE*save;
save=fopen("save.txt","w");
	savecheck=2;
	if(save==NULL){
		printf("\nThere was an issue opening the save file");
		return 1;
	}
	/*1-death 2-main 3-exit(closing grimbalde option tree*/
	/*1-attack, 2-strength, 3-defense, 4-magic, 5-range, 6-speed, 7-ch_health, 8-bing_bongs, 9-name, 10-dead_sarah 11-dead_addict 12-dead_rat 13-23-itemcheck array
	 24-34 Food 35-45-itemstatus 46-Kills*/
	fprintf(save,"%d\n",(int)savecheck);
	fprintf(save,"%d\n",(int)attack);
	fprintf(save,"%d\n",(int)strength);
	fprintf(save,"%d\n",(int)defense);
	fprintf(save,"%d\n",(int)magic);
	fprintf(save,"%d\n",(int)range);
	fprintf(save,"%d\n",(int)speed);
	fprintf(save,"%d\n",(int)ch_health);
	fprintf(save,"%d\n",(int)bing_bongs);
	fprintf(save,"%s\n",name);
	fprintf(save,"%d\n",dead_sarah);
	fprintf(save,"%d\n",dead_addict);
	fprintf(save,"%d\n",dead_rat);
		for(y==0;y<=10;y++){
			fprintf(save,"%d\n",itemcheck[y]);
		}
		y=0;
		for(y==0;y<=10;y++){
			fprintf(save,"%d\n",food[y][0]);
		}
		y=0;
		for(y==0;y<=10;y++){
			fprintf(save,"%d\n",item_status[y]);
		}
		fprintf(save,"%d\n",kills);
	printf("\n............Finished Saving............\n");
	fclose(save);
		if(num==1){
			printf("\nClosing Grimblade\n");
		}
		else if(num==2){
			back("exit");
		}
		else if(num==3){
			printf("\nClosing Grimblade\n");
			exit(0);
		}
}
int recover (int reading){
int bofa,y=0;
FILE*read;
read=fopen("save.txt","r");
	if(read==NULL){
		printf("\nThere was an issue opening the save file");
		return 1;
	}
	if(reading==7){
		fscanf(read,"%d",&savecheck);
		initialcheck=2;
		back("recover");
		fclose(read);
	}
	else{
	
		/** 1 is actually savecheck. 1-attack, 2-strength, 3-defense, 4-magic, 5-range, 6-speed, 7-ch_health, 8-bing_bongs, 9-name, 10-dead_sarah 11-dead_addict 
		12-dead_rat 13-23-itemcheck array 24-34 Food 35-45-itemstatus 46-Kills*/
		fscanf(read,"%d\n",&bofa);
		fscanf(read,"%d\n",&attack);
		fscanf(read,"%d\n",&strength);
		fscanf(read,"%d\n",&defense);
		fscanf(read,"%d\n",&magic);
		fscanf(read,"%d\n",&range);
		fscanf(read,"%d\n",&speed);
		fscanf(read,"%d\n",&ch_health);
		fscanf(read,"%d\n",&bing_bongs);
		fscanf(read,"%s\n",&name);
		fscanf(read,"%d\n",&dead_sarah);
		fscanf(read,"%d\n",&dead_addict);
		fscanf(read,"%d\n",&dead_rat);
			for(y==0;y<=9;y++){
				fscanf(read,"%d\n",&itemcheck[y]);
			}
		y=0;
			for(y==0;y<=9;y++){
				fscanf(read,"%d\n",&item_status[y]);
			}
		fscanf(read,"%d",&kills);
		fclose(read);
		if(reading==1){
			noob=2;
			back("exit");
		}
	}
}
int bofaland (int bofa){
	
}




/*END OF FILE */


