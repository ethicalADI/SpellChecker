#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    char data;
    bool is_last;
    unordered_map<char, Node*> children;

    Node(char d) {
        data = d;
        is_last = false;
    }
};

class Trie {
    Node *root;
    Node *tmp;

public:
    Trie() {
        root = new Node('\0');
    }

    // Add a word to the trie
    void add_word(string word) {
        Node *temp = root;

        for (int i = 0; i < word.length(); i++) {
            char ch = word[i];

            if (temp->children.count(ch)) {
                temp = temp->children[ch];
            } else {
                Node *n = new Node(ch);
                temp->children[ch] = n;
                temp = temp->children[ch];
            }
        }

        temp->is_last = true;
        cout << "\n\t\t\t\t\t\t Entry Added Successfully \n";
    }

    // Search for a word in the trie
    bool search_by_word(string word) {
        Node *temp = root;
        for (int i = 0; i < word.length(); i++) {
            char ch = word[i];
            if (!temp->children.count(ch)) {
                return false;
            }

            temp = temp->children[ch];
        }

        return temp->is_last;
    }

    // Search for words with a given prefix
    bool search_with_prefix(string prefix) {
        Node *temp = root;

        for (int i = 0; i < prefix.size(); i++) {
            char ch = prefix[i];
            if (!temp->children.count(ch)) {
                return false;
            }

            temp = temp->children[ch];
        }
        tmp = temp;
        return true;
    }

    // Display all words in the trie
    void display_by_word() {
        string word;
        cout << "\t\t\t\t\t\t Enter the word to display: ";
        cin >> word;
        if (search_by_word(word)) {
            cout << "\n\t\t\t\t\t\t Word: " << word << "\n";
        } else {
            cout << "\n\t\t\t\t\t\t Word not found!\n";
        }
    }

    // Display all words starting with a given prefix
    void display_with_prefix() {
        string prefix;
        cout << "\t\t\t\t\t\t Enter the prefix: ";
        cin >> prefix;
        if (search_with_prefix(prefix)) {
            cout << "\n\t\t\t\t\t\t Words with prefix '" << prefix << "':\n";
            build_words(tmp, prefix.substr(0, prefix.length() - 1));
        } else {
            cout << "\n\t\t\t\t\t\t No words found with the prefix!\n";
        }
    }

    // Build words from a given node
    void build_words(Node *temp, string curr) {
        if (temp->is_last) {
            cout << "\t\t\t\t\t\t " << curr + temp->data << endl;
        }
        for (auto &child : temp->children) {
            build_words(child.second, curr + temp->data);
        }
    }

    // Delete a word from the trie
    void delete_by_word(string word) {
        Node *temp = root;
        bool check = true;

        for (int i = 0; i < word.length(); i++) {
            char ch = word[i];
            if (!temp->children.count(ch)) {
                check = false;
                break;
            } else {
                temp = temp->children[ch];
            }
        }

        if (check && temp->is_last) {
            temp->is_last = false;
            cout << "\n\t\t\t\t\t\t Entry Deleted Successfully \n";
        } else {
            cout << "\n\t\t\t\t\t\t Invalid!! Please Enter a valid word\n";
        }
    }

    // Delete all words starting with a given prefix
    void delete_with_prefix(string prefix) {
        Node *temp = root;

        if (!search_with_prefix(prefix)) {
            cout << "\n\t\t\t\t\t\t Invalid!! Please Enter a valid Prefix\n";
            return;
        }

        delete_nodes(tmp);
        tmp->children.clear();
        tmp->is_last = false;
        cout << "\n\t\t\t\t\t\t Entries Deleted Successfully\n";
    }

    // Delete all nodes from a given node
    void delete_nodes(Node *node) {
        for (auto &child : node->children) {
            delete_nodes(child.second);
        }
        delete node;
    }
};

int menu() {
    cout << "\n";
    cout << "\t\t\t\t\t--------------------------------------------\n";
    cout << "\t\t\t\t\t|               DICTIONARY                 |\n";
    cout << "\t\t\t\t\t--------------------------------------------\n";
    cout << "\t\t\t\t\t|                                          |\n";
    cout << "\t\t\t\t\t|       [1]  Add Word                      |\n";
    cout << "\t\t\t\t\t|       [2]  Search by Word                |\n";
    cout << "\t\t\t\t\t|       [3]  Search by Prefix              |\n";
    cout << "\t\t\t\t\t|       [4]  Display by Word               |\n";
    cout << "\t\t\t\t\t|       [5]  Display by Prefix             |\n";
    cout << "\t\t\t\t\t|       [6]  Delete by Word                |\n";
    cout << "\t\t\t\t\t|       [7]  Delete by Prefix              |\n";
    cout << "\t\t\t\t\t|       [8]  Exit                          |\n";
    cout << "\t\t\t\t\t--------------------------------------------\n";
    cout << "\n";
    cout << "\t\t\t\t\tEnter your choice : ";

    int choice;
    cin >> choice;

    return choice;
}

int main() {
    Trie *t = new Trie();

    int choice = menu();
    do {
        if (choice == 1) {
            cout << "\t\t\t\t\t\t Please Enter Word : ";
            string s;
            cin >> s;

            if (t->search_by_word(s)) {
                cout << "\n\t\t\t\t\t\t Entry already exists\n";
            } else {
                t->add_word(s);
            }
        }
       else if (choice == 2) {
            cout << "\t\t\t\t\t\t Please Enter word to search: ";
            string s;
            cin >> s;
            bool ok = t->search_by_word(s);
            if (ok)
                cout << "\n\t\t\t\t\t\t Word exists.\n";
            else
                cout << "\n\t\t\t\t\t\t Word does not exist!!\n";
        } 
       else if (choice == 3) {
            cout << "\t\t\t\t\t\t Please Enter prefix to search: ";
            string s;
            cin >> s;

            bool ok = t->search_with_prefix(s);
            if (ok)
                cout << "\n\t\t\t\t\t\t Words exist with this prefix.\n";
            else
                cout << "\n\t\t\t\t\t\t Words do not exist with this prefix\n";
        } 
       else if (choice == 4) {
            t->display_by_word();
        } 
       else if (choice == 5) {
            t->display_with_prefix();
        } 
       else if (choice == 6) {
            cout << "\t\t\t\t\t\t Please Enter word to delete: ";
            string n;
            cin >> n;
            t->delete_by_word(n);
        } 
       else if (choice == 7) {
            cout << "\t\t\t\t\t\t Please Enter prefix to delete words: ";
            string p;
            cin >> p;
            t->delete_with_prefix(p);
        } 
       else {
            break;
        }

        choice = menu();
    } while (choice <= 7 && choice >= 1);

    cout << "\n\t\t\t\t\t\t\tTHANK YOU !";

    return 0;
}
