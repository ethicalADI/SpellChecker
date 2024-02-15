#include<bits/stdc++.h> 
using namespace std;  

class Node
{
    public:
        char data;

        pair<bool,string> is_last;

        unordered_map<char,Node*> children;
        
        Node(char d)
        {
            data = d;
            is_last.first=false;
            is_last.second="-1";
        }
};


class Trie
{
    Node *root;
    Node* tmp;

public:
    //Initialize trie data structure here

    Trie()
    {
        root=new Node('\0');
    }

    //Inserting a word into the trie

    void insert(string word,string definition)
    {
        Node* temp = root;

        for(int i=0;i<word.length();i++)
        {
            char ch = word[i];

            if(temp->children.count(ch))
            {
                temp = temp->children[ch];
            }
            else
            {
                Node *n = new Node(ch);
                temp->children[ch]=n;
                temp = temp->children[ch];
            }
        }

        temp->is_last.first = 1;
        temp->is_last.second = definition;
        cout<<"\n\t\t\t\t\t\t Entry Added Successfully \n";
    }


    //Returns if the word is in the trie

    bool search(string word)
    {
        Node *temp= root;
        for(int i=0;i<word.length();i++)
        {
            char ch = word[i];
            if(!temp->children.count(ch))
            {
                return false;
            }

            temp = temp->children[ch];
        }

        if(temp->is_last.first==1)
        {
            return true;
        }
        return false;
    }



    bool starts_with(string prefix)
    {
        Node* temp=root;

        for(int i=0;i<prefix.size();i++)
        {
            char ch = prefix[i];
            if(!temp->children.count(ch))
            {
                return false;
            }

            temp = temp->children[ch];
        }
        tmp=temp;
        return true;
    }

    //Remove the word if exists

    void remove(string word)
    {
        Node *temp= root;

        bool check=true;

        for(int i=0;i<word.length();i++)
        {
            char ch = word[i];
            if(!temp->children.count(ch))
            {
                check=false;
            }
            else
            {
                temp = temp->children[ch];
            }
        }

        if(check)
        {
            temp->is_last.first=false;
            cout<<"\n\t\t\t\t\t\t Entry Deleted Successfully \n";
            return;
        }
        else
        {
            cout<<"\n\t\t\t\t\t\t Invalid!! Please Enter a valid word\n";
        }
    }

    void build_words(Node *temp,string curr)
    {
        for(char c='a';c<='z';c++)
        {
            if(temp->children.count(c))
                build_words(temp->children[c],curr+temp->data);

            else
            {
                if(temp->is_last.first)
                {
                    cout<<"\t\t\t\t\t\t ";
                    cout<<curr+temp->data<<": " << temp->is_last.second <<endl;
                    return;
                }
            }
        }

    }

    //Show recommendations according to the given word

    void show_recommendations(string incom_word)
    {
        Node *temp = root;

        if(!starts_with(incom_word))
        {
            cout<<"\n\t\t\t\t\t\t Invalid!! Please Enter a valid Prefix\n";
            return ;
        }
        else
        {
            string cpy = incom_word;
            cpy.pop_back();

            build_words(tmp,cpy);
        }
    }
};

int menu()
{
    cout<<"\n";
    cout<<"\t\t\t\t\t--------------------------------------------\n";
    cout<<"\t\t\t\t\t|               DICTIONARY APP             |\n";
    cout<<"\t\t\t\t\t--------------------------------------------\n";
    cout<<"\t\t\t\t\t|                                          |\n";
    cout<<"\t\t\t\t\t|       [1]  Add Word & Meaning            |\n";
    cout<<"\t\t\t\t\t|       [2]  Search by Word                |\n";
    cout<<"\t\t\t\t\t|       [3]  Search by Prefix              |\n";
    cout<<"\t\t\t\t\t|       [4]  Show Words with Prefix        |\n";
    cout<<"\t\t\t\t\t|       [5]  Delete Word                   |\n";
    cout<<"\t\t\t\t\t|       [6]  Exit                          |\n";
    cout<<"\t\t\t\t\t--------------------------------------------\n";
    cout<<"\n";
    cout<<"\t\t\t\t\tEnter your choice : ";

    int choice;
    cin>>choice;
    
    return choice;
}


int main()
{    
    Trie *t = new Trie();

    int choice = menu();
    do
    {

        if(choice==1)
        {

            cout<<"\t\t\t\t\t\t Please Enter Word : ";
            string s, definition;
            cin>>s;
            cout<<"\t\t\t\t\t\t Please Enter Meaning : ";
            cin.ignore(); // Clear input buffer
            getline(cin, definition);
            
            if(t->search(s))
            { 
                cout<<"\n\t\t\t\t\t\t Entry already exists\n";
            }
            else
            {
                t->insert(s, definition);
            }
       }

       else if(choice==2)
       {

        cout<<"\t\t\t\t\t\t Please Enter word to search: ";
        string s;
        cin>>s;
        bool ok = t->search(s);
        if(ok)
            cout<<"\n\t\t\t\t\t\t Word exists. "  << "\n";
        else
            cout<<"\n\t\t\t\t\t\t Word does not exist !! \n";

        }

        else if(choice==3)
       {

        cout<<"\t\t\t\t\t\t Please Enter prefix to search: ";
        string s;
        cin>>s;
        
        bool ok = t->starts_with(s);
        if(ok)
            cout<<"\n\t\t\t\t\t\t Words exist with this prefix. \n";
        else
            cout<<"\n\t\t\t\t\t\t\t\t\t\t Words does not  exist with this prefix\n";

        }
       else if(choice==4)
        {

            cout<<"\t\t\t\t\t\t Please Enter the prefix: ";
            string na;
            cin>>na;

            t->show_recommendations(na);
        }
        else if(choice==5)
        {

            cout<<"\t\t\t\t\t\t Please Enter word to delete : ";
            string n;
            cin>>n;
            t->remove(n);

        }

        
        else
        {
            break;
        }

        choice=menu();
    }

    while(choice<=5 && choice>=1);

    cout<<"\n\t\t\t\t\t\t\tTHANK YOU !";

    return 0;
}
