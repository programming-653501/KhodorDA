//---------------------------------------------------------------------------

#include <stdio.h>
#pragma hdrstop

#include <conio.h>
#include <tchar.h>
//---------------------------------------------------------------------------
#include <malloc.h>
#include <stdlib.h>
#pragma argsused

struct Word
{
	char* word;
	int length;


};


bool Equal(Word* word1, Word* word2)
{
	if(word1 != NULL && word2 != NULL)
	{
		if(word1->length != word2->length)
		{
			return false;
		}

		char* pointer1 = word1->word;
		char* pointer2 = word2->word;

		while(*pointer1 != '\0')
		{
			if(*pointer1 != *pointer2)
			{
				return false;
			}
			pointer1++;
			pointer2++;
		}

		return true;
	}
	return false;
}

void Swap(Word* word1, Word* word2)
{
	Word temp = *word1;
	*word1 = *word2;
	*word2 = temp;
}

int CompareByLengthMax( Word* word1, Word* word2)
{
	 if(word1 != NULL && word2 != NULL)
	 {
		if(word1->length > word2->length)
		{
			return 1;
		}
		else
		{
			if(word1->length == word2->length)
			{
				return 0;
			}
			else
			{
				return -1;
			}
		}

	 }
	 else
	 {
         return -2;
     }
}

int CompareByLengthMin(Word* word1, Word* word2)
{
	return CompareByLengthMax( word2, word1 );
}



class WordArray
{
	private:
	Word** _word_array;
	int _length;
	int _words_amount;

	public:
	WordArray(char* text)
	{
		_word_array =  ( Word**)malloc(sizeof(Word*) * 2);
		_length = 2;
		SeparateToWords(text);
	}


	private:
	void SeparateToWords(char* text)
	{

		 int WordCounter = 0;
		 char* pointer = text;

		 while(*pointer != '\0')
		 {

			 int WordLength = 0;


			 char ch = *(pointer + WordLength  );

			 while(ch != ' ' && ch != '\0')
			 {
				 WordLength++;
				 ch = *(pointer + WordLength );
			 }

			  _word_array[ WordCounter ] = (Word*)malloc( sizeof(Word) );
			  _word_array[ WordCounter ]->word = (char*)malloc( sizeof(char) * WordLength + 1);
			  _word_array[ WordCounter ]->length= WordLength;

			 int i = 0;
			 while( i < WordLength)
			 {
				 (_word_array[ WordCounter ]->word)[i] = (*pointer);
				 pointer++;
				 i++;
			 }

			 (_word_array[ WordCounter ]->word)[i] = '\0';
			 if(*pointer != '\0')
			 {
				pointer++;
			 }
			 WordCounter++;

			 if(_length == WordCounter)
			 {
				 WordArrayResize();
			 }

		 }

		 _words_amount = WordCounter;
	}



	void WordArrayResize()
	{
		_word_array = (Word**)realloc( _word_array , sizeof(Word*)*_length*2);
		_length*=2;
	}





	void Sort(int (*CompareFunction) (Word*,Word*) )
	{

			 int i;
			 for(i = 0; i < _words_amount - 1; i++)
			 {
				 int j;
				 Word* chosen = _word_array [i];

				 for(j = i + 1; j < _words_amount; j++)
				 {
					 if( (*CompareFunction)(_word_array [j], chosen)  == 1 )
					 {
						chosen = _word_array [j];
					 }
				 }

				 Swap(_word_array[i], chosen);
			 }

	}
	void PrintWords(int (*CompareFunction) (Word*,Word*))
	{
			int i = 0;

			Sort(CompareFunction);
			printf("the length is %d\n", _word_array[0]->length ) ;
			do
			{
				 bool already_printed = false;
				 for(int j = 0; j < i; j++)
				 {
					 if( Equal(_word_array[i],_word_array[j]) )
					 {
						 already_printed = true;
						 break;
                     }
                 }
				 if(!already_printed)
				 {
					printf("%s\n", _word_array[i]->word);
				 }
				 i++;
			}while( (*CompareFunction)( _word_array [i-1] , _word_array [i] ) == 0 &&  i < _words_amount );
			printf("\n");

	}

	public:
	void PrintLongestWords()
	{
		printf(" the longest words\n\n");
		PrintWords(CompareByLengthMax);
	}
	void PrintShortestWords()
	{
		printf(" the shortest words\n\n");
		PrintWords(CompareByLengthMin);
    }



	~WordArray()
	{
		for(int i = 0; i < _words_amount; i++)
		{
			free(_word_array[i]->word);
			free(_word_array[i]);
		}
		free(_word_array);
	}


};



int _tmain(int argc, _TCHAR* argv[])
{
	char* text;

	text = (char*)malloc(sizeof(char) * 2000);
	gets(text);
	printf("\n");
	WordArray* MyArray = new WordArray(text);

	MyArray->PrintLongestWords();
	MyArray->PrintShortestWords();


	free(MyArray);
	free(text);
	getch();
	return 0;
}
//---------------------------------------------------------------------------
