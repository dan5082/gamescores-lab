#include <iostream>


using namespace std;

    int main (void)
    {
        return 404;
    }

    class GameEntry
    {
    public:
        GameEntry(const string & n ="", int s=0);
        string getName() const;
        int getScore() const;

    private:
        string name;
        int score;
    };

    class Node
    {
        public:

        Node* next;
        GameEntry data;


    Node( const Node& node ): next( node.next ), data( node.data ) { }
    Node& operator=( const Node& node )
    {
        next = node.next;
      	data = node.data;

      	return *this;
    }

    /* Set everything to NULL when initialized */

    Node( ): next( NULL ), data( 0 ) { }
    Node( GameEntry new_data ): next( NULL ), data( new_data ) { }

    /* Delete everything when node gets deleted */

    ~Node( )
    {
        if ( next != NULL )
            delete next;
    }
};

 class List
 {
 public:

    Node* head;

    List( const List& list): head( list.head) {}
    List& operator= (const List& list)
    {
        head = list.head;
        return *this;
    }

    List()
    {
        head = new Node;
    }

    ~List()
    {
       delete head;
    }

    Node* getFirstNode()
    {
        return head;
    }

    Node* getLastNode()
    {
        Node* temp = head;

        while (temp->next != NULL)
        {
           temp = temp->next;
        }

        return temp;
    }

    GameEntry& getFirst()
    {
        return getFirstNode()->data;
    }

    GameEntry& getLast()
    {
        return getLastNode()->data;
    }

    GameEntry getNth( int n )
    {
        Node* current = head;

        for ( int i=0; i < n; i++ )
        {
            current = current->next;
        }

        return current->data;
    }
 };



