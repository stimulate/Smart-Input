        /// Author: Sabrina Yu

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>


#define LIMIT 10
#define MAX 256//specify the maximum number of letters  constitute a word 
#define MAXLEN 1024 
int uniqueness = 0;
char lastWord[MAXLEN];

typedef struct TrieNode
{
	int path;//the word path on which the letters combine
    int count;
    struct TrieNode *next[MAX];
}TrieNode;  

        /// <summary>
        /// Insert one word into the trie 
        /// </summary>
        /// <param name="*word">a word of char type</param>
        /// <param name="*root">the root node of trie</param>
		int Insert(char *word,TrieNode *root)
		{
		    int i;
		    TrieNode *cur;
		    if(word[0]=='\0')
		        return 0;
		    cur=root;
		    for(i=0;word[i]!='\0';i++)
		    {
		        if(cur->next[word[i]]==NULL)
		        {
		            TrieNode *newNode = (TrieNode *)malloc(sizeof(TrieNode));
		            memset(newNode,0,sizeof(TrieNode));
		            cur->next[word[i]]=newNode;
		        }
		        cur=cur->next[word[i]];
				cur->path++;
		    }
		    cur->count++;
		    return 1;
		}
        /// <summary>
        /// Add a new word into the file of dictionary 
        /// Each word on a new line 
        /// </summary>
		void AddWord()
		{
			FILE *fp;
			char a[MAX];
			if((fp = fopen("google-10000-english.txt","a+"))==NULL)
			{
				fprintf(stdout, "Cannot open this file!\n");
			exit(1);
			}
			puts("Enter a word to add to the dictionary: press the Enter\n");
			//while (gets(a)!= NULL && a[0] != '\0')
			while(gets(a)!=NULL && a[0]>='a'&&a[0]<='z'||gets(a)!=NULL &&a[0]>='A'&&a[0]<='Z')
				{
				fprintf(fp,"\n%s",a);
				puts("Add successfully");}
		
			if(fclose(fp) != 0)
				fprintf(stderr, "Error closing file\n");
		}
		
		 /// <summary>
        /// Populate the tree using data in the dictionary file 
        /// </summary>
        /// <param name="*&root">the root node of trie</param>
		void Construct(TrieNode *&root)
		{
			char filename[] = "google-10000-english.txt"; //the file name of dictionary 
			int ret = 0;
		    FILE *fp; 
		    char StrLine[MAXLEN];             //specify the maximum length of word program will read 
			memset(StrLine,'\0',MAXLEN);
			int i;
			root = (TrieNode *)malloc(sizeof(TrieNode));
			 memset(root,0,sizeof(TrieNode));
		    if((fp = fopen(filename,"r")) == NULL) //test whether the file exists and be readable 
		    { 
		        printf("error!"); 
		        return ; 
		    } 
  
		    while (!feof(fp)) 
		    { 
		        fgets(StrLine,MAXLEN,fp);  //read the data of the file line by line 
				for(i = 0;i < MAXLEN;i++)
				{
					if(StrLine[i] == '\n')
					{
						StrLine[i] = '\0';
						break;
					}
				}		        
				ret = Insert(StrLine,root);
				if(ret == 0)
					printf("Fail to insert\n");
		    } 
		    fclose(fp); //close the file 
		
		    return;
		}
		
		 /// <summary>
        ///  Traverse the whole trie 
        /// </summary>
        /// <param name="*curP">the current node of trie</param>
		void Traverse(TrieNode *curP)
		{
		    static char theWord[MAXLEN];
		    static int pos=0; 
		    int i;
		    if(curP==NULL)
		        return;
		    if(curP->count)
		    {
		        theWord[pos]='\0';
		        printf("%s:%d\n",theWord,curP->count);
		    }
		    for(i=0;i<MAX;i++)
		    {
		        theWord[pos++]=i; 
		        Traverse(curP->next[i]); 
		        pos--;  
		    }
		    return;
		}
		
		/// <summary>
        /// Find the word according to the prefix info which user input
		/// and print out it if conditions meeted
        /// </summary>
        /// <param name="*curP">the current node of trie</param>
        /// <param name="*str">the root node of trie</param>
		void Showprefix(TrieNode *curP,char *str)
		{
		    static char theWord[MAXLEN];
		    static int pos=0; 
		    int i;
		    if(curP==NULL)
		        return;
		    if(curP->count)
		    {
		        theWord[pos]='\0';
				printf("%s%s:%d\n",str,theWord,curP->count);
				uniqueness++;
			//if the variable uniqueness equals 1 print out the word
				if(uniqueness == 1)
					sprintf(lastWord,"%s%s\0",str,theWord);
				else
					memset(lastWord,'\0',MAXLEN);
		    }
		    for(i=0;i<MAX;i++)
		    {
		        theWord[pos++]=i; 	
		        Showprefix(curP->next[i],str); 
		        pos--;  
		    }
		    return;
		}
		
		 /// <summary>
        /// Find if the word entered is in the trie 
        /// </summary>
        /// <param name="*root">the root node of trie</param>
        /// <param name="*word">the input word of char type</param>
		bool Find(TrieNode *root,char *word)
		{
		    int i;
		    TrieNode *cur;
		    cur=root;
		    for(i=0;word[i]!='\0';i++)
		    {
		        if(cur->next[word[i]]==NULL)
		        {
		            return false;
		        }
		        cur=cur->next[word[i]];
		    }
			Showprefix(cur,word);
		}
		
        /// <summary>
        /// Find the number of existing words in the trie
		/// with the prefix of what user has entered 
        /// </summary>
        /// <param name="*root">the root node of trie</param>
        /// <param name="*word">the input word of char type</param>
        /// <returns>the number of existing words in the trie, i of int type</returns>
		int prefixnumber(TrieNode* root, char *word){  
			int i;
		    TrieNode *cur;
		    cur=root;
		    for(i=0;word[i]!='\0';i++)
		    {
		        if(cur->next[word[i]]==NULL)
		        {
		            return false;
		        }
		        cur=cur->next[word[i]];
		    }
		
		   return cur->path;
		} 
		
		int main()  
		{  
		
		    TrieNode *root;
			char ch;
			int i = 0,count = 0;
		    char str[MAXLEN];
			memset(str,'\0',MAXLEN);
		    Construct(root);  
		    printf("\n");  
		    //show different options to users
		    int choice;
			menu:printf("\t\t\t1.Input a word:\n"); // this is the word predictor
			  printf("\t\t\t2.Add a new word\n"); // Add a new word into file
			  printf("\t\t\t0.Exit system\n\n");
			  printf("\t\t\tPlease enter choice(0~2)");
			  scanf("%d",&choice);
			  switch(choice)
			   {
			    case 1:
		
		    while(1)
		    {
				//clear the screen
				while (!_kbhit())
					break;
				ch = _getch();
				fflush(stdin);
				system("cls");
				printf("\t\t\tPlease input a word:\n");
				if(ch == 9)
				{
					if(str[0] == '\0')
					{
						printf("\t\t\tPlease input a word:\n");
						continue;
					}
					Find(root,str);
					if(uniqueness == 1)
					{
						printf("%s\n",lastWord);
						i = 0;
						memset(str,'\0',MAXLEN);
					}
					else
						printf("%s",str);
					continue;
				}
				str[i++] = ch;
				str[i] = '\0';
				
				count = prefixnumber(root,str);
				//when the number of matching words are less than 10
				//print them out in the screen
				//if more than 10, show the number
				if(count < LIMIT)
				{
					Find(root,str);
					uniqueness = 0;
				}
				else
					printf("%s:%d\n",str,count);
				/*if the word not found, sound the alarm*/
				if(count == 0)
				{
					i = 0;
					printf("%s:%d\n",str,count);
					memset(str,'\0',MAXLEN);
					printf("\a");
				}
				printf("%s",str);
				if(ch == '*')
					break;
		    }break;
			    case 2:
					//clear the screen
					while (!_kbhit())
					AddWord();					
					system("cls");			
					break;	    
			    case 0:exit(0);
			  }
			 //if(choice<0||choice>2)printf("\n\n\n\t\tPlease choose again!\n\n");
			 // goto menu;
		
		    return 0;  
		} 
