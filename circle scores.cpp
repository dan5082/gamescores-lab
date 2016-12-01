#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;


    class GameEntry
    {
    public:
        GameEntry(const string & n, int s): name( n ), score( s ) { }
        GameEntry( ): name( "N/A" ), score( 0 ) { }
        string getName() const;
        int getScore() const;

        void setName( string n )
        {
            name = n;
        }

        void setScore( int s )
        {
            score = s;
        }

        int getScore()
        {
            return score;
        }
        string getName()
        {
            return name;
        }

    private:
        string name;
        int score;
    };

    class Node
    {
        public:

        Node* next;
        Node* before;
        GameEntry data;


    Node( const Node& node ): next( node.next ), data( node.data ), before(node.before) { }
    Node& operator=( const Node& node )
    {
        next = node.next;
      	data = node.data;
      	before = node.before;

      	return *this;
    }

    /* Set everything to NULL when initialized */

    Node( ): next( NULL ),before( NULL), data( ) { }
    Node( GameEntry new_data ): next( NULL ), before( NULL), data( new_data ) { }
};

 class List
 {
 public:

    Node* head;
    Node* tail;


    List( const List& list ): head( list.head), tail(list.tail) {}

    List& operator= (const List& list)
    {
        head = list.head;
        return *this;
    }

    List()
    {
        head = NULL;
        tail = NULL;
    }

    ~List()
    {
       Node* temp ;
       Node* current = head->next;
       delete head;
       tail->next = NULL;
      // cerr << "Deconstruction has started"; debugging

       while (temp != NULL)
       {
           temp = current->next;
           delete current;
           current = temp;
       }

       //cerr << "Deconstruction has finished";  debugging
    }

    Node* getFirstNode()
    {
        return head;
    }

    Node* getLastNode()
    {
        return tail;
    }

    void printAllData()
    {
         Node* temp = head;
         int place =1;
         cout << "\n"<<place<< '|'<<temp->data.getScore()<<'|'<<temp->data.getName()<<endl;

        if (head->next !=head)
        {
            do  // this will print all of them
            {
                place++;
                temp = temp->next;
                cout << "\n"<<place<< '|'<<temp->data.getScore()<<'|'<<temp->data.getName()<<endl;
            }while (temp->next != head) ;
        }

        //cerr << "\nData Printed good\n";

    }

    unsigned int numberOfNodes(void)
    {
        unsigned int nodes=1;
        Node* temp = head;
         while (temp->next != head)
        {
            nodes++;

           temp = temp->next;

        }
        return nodes;


    }

    GameEntry& getFirst()
    {
        return getFirstNode()->data;
    }

    GameEntry& getLast()
    {
        return getLastNode()->data;
    }

    GameEntry& getNth( int n )
    {
        Node* current = head;

        for ( int i=0; i < n; i++ )
        {
            current = current->next;
        }

        return current->data;
    }

    void insert( string name, int score )
    {
        if ( head == NULL )
        {
            //cerr << "\n\nhead was NULL\n"; //debugging
            head = new Node( GameEntry( name, score ) );
            head->next = head;
            head->before = head;
            tail = head;
        }
        else if ( score > head->data.getScore( ) )
        {
            /* Check if the score should be placed at the first slot */

            Node* oldHead = head;
            head = new Node( GameEntry( name, score ) );
            head->next = oldHead;
            oldHead->before = head;
            head->before = tail;
            tail->next = head;
            if(oldHead->next == tail)
            {
                tail=oldHead;
            }
        }
        else
        {
            cerr << "\n\ni took an else\n";//debugging
            Node* current = head;
            Node* originalNext;
            bool looping = true;

            while ( looping )
            {
				if ( current->next != head && current->next->data.getScore( ) > score )
				{
					current = current->next;
				}
				else
				{
					looping = false;
                }
            }

           // cerr << "while loop passed";
            originalNext = current->next;


            Node* newInsert= new Node(GameEntry(name,score));
			newInsert->next = current->next;
          //  cerr << "about to run 221";  debugging
			current->next = newInsert;
			//cerr << "about to run 223";
			newInsert->before = current;
			//cerr << "about to run 225";
			if(originalNext != head)
            {
                originalNext->before = newInsert;
            }

			//cerr <<"\nInsertion passed";

			if(newInsert->next == head)
            {
                tail = newInsert;
                tail->next = head;
            }

        }
    }

    void removeNthNode(unsigned long n)
    {
        int frontHops = n;
        int backHops = numberOfNodes() - n;
        Node* newBefore;
        Node* newNext;

        if(numberOfNodes()== 1)
        {
           // cerr << "i took first branch";
            head->next= NULL;
            head->before=NULL;
            delete head;
            cout << "There are no more high scores!";
            cout << "Thanks for using the program !";
            exit(0);
        }

        else if (n == numberOfNodes())
        {
            Node* newTail = tail->before;
            newTail->next = head;
            tail->before = NULL;
            tail->next = NULL;
            delete tail;
            tail = newTail;

        }
        else if(backHops < frontHops)
        {
             Node* current = tail;
            for(int i =0;i<backHops;i++)
            {
               current = current->before;
            }
          //  cerr << "loop passed";
           // cerr << "\n\nDeleting " << current->data.getName( ) << std::endl;
            newBefore = current->before;
           // cerr << "255\n";
            newNext = current->next;
           // cerr << "257\n";
            newBefore->next = newNext;
           // cerr << "259\n";
            newNext->before = newBefore;
           // cerr << "262\n";
            current->next = NULL;
            current->before = NULL;
            delete current;
           // cerr << "\ncurrent has been delete";


        }
        else if(n == 1)
        {
            Node* oldHead = head;
            head = head->next ;
            head->before = tail;
            tail->next = head; //new

            oldHead->next = NULL;
            oldHead->before = NULL;
            delete oldHead;

            //cerr <<"\n\n I delete the head succsess\n";

        }
        else
        {
            Node* current = head;
            for(int i =0;i<frontHops-1
            ;i++)
            {
               current = current->next;
            }
            newBefore = current->before;
            newNext = current->next;
            newBefore->next = newNext;
            newNext->before = newBefore;
            current->next = NULL;
            current->before = NULL;
            delete current;
        }




    }


 };

    int main (void)
    {
        List scores;


       // List scores;
        int score;
        string name;
        char choice;

        cout << "Hello Welcome to the TOTALLY AWESOME Dually-Linked High-Score Storing Program!\n\n" << endl;
        do{

                //storing the name and score from the player
        cout << "What's your name?:";
        cin >> name;

        cout << "What's the score?:";
        cin >> score;


        //putting in the score into the linked list
        scores.insert(name,score);

        //condition for another score
        cout << "\nScore has been stored. Would you like to add another? [y/n]" <<endl;;
        cin>> choice;
        }while(tolower(choice)== 'y');
        scores.printAllData();

        cout << "\t\n\nthe number of nodes is : " << scores.numberOfNodes() << endl;

        int run=0;

        do{

                    do
                    {
                        cout << "\n\nWould you like to delete a high score?[y/n]:  ";
                        cin >> choice;
                        run++;
                    }while(choice != 'y' && choice != 'n' && run == 0);

            unsigned long removeThis;
            if (tolower(choice) == 'y')
            {
                cout << "Please Enter the number of the score you wish to remove";
                cin >> removeThis;
                while(removeThis > scores.numberOfNodes())
                {
                    cerr <<"ERROR: YOU ARE TRYING TO REMOVE A SCORE THAT DOESNT EXIST\n\n";
                    cerr << "Please try again: ";
                    cin >> removeThis;
                }
                scores.removeNthNode(removeThis);
                cout << "\n\nScore: "<< removeThis << "has been deleted.";
            }

                cout << "The high scores are:\n\n";
                scores.printAllData();
                if(choice !='y')
                    {
                        do
                        {
                            cout << "\n\nWould you like to delete a high score?[y/n]:  ";
                            cin >> choice;

                        }while(choice != 'y' && choice != 'n');
                    }
        }while(tolower(choice)=='y');


        //cout << "\nLOOP HAS BEEN EXITED";  debugging

        return 0;

    }

/*
*  One of the advantages of using a circular doubly linked list in this situation is that we can automatically loop around
* from the last node to the front. This is good in this situation because we could use the 10th node which is the lowest
* high-score and see if the new score is greater than it. if it is than we could compare it to next and so on.
* This would be efficient as most scores would probably not be high-scores.
*
*
*
*
*
*
*/

