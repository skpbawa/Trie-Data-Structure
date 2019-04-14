#include<bits/stdc++.h>

using namespace std;

struct trieNode
{
    struct trieNode *children [26];
    bool isEnd;
};

struct trieNode * getNode ()
{
    struct trieNode *newNode = new struct trieNode;

    for (int i = 0; i < 26; i ++)
    {
        newNode -> children [i] = NULL;
    }

    newNode -> isEnd = false;

    return newNode;
}

void insertRecursively (struct trieNode *curr, string key, int depth)
{
    if (depth == key.length ())
    {
        curr -> isEnd = true;
    }
    else
    {
        int index = key [depth] - 'a';
        if (curr -> children [index] == NULL)
        {
            curr -> children [index] = getNode ();
        }
        curr = curr -> children [index];
        insertRecursively (curr, key, depth + 1);
    }
}

void insert (struct trieNode *root, string key)
{
    insertRecursively (root, key, 0);
}

struct trieNode *search (struct trieNode *curr, string key)
{
    for (int i = 0; i < key.length (); i ++)
    {
        int index = key [i] - 'a';
        if (curr -> children [index] != NULL)
        {
            curr = curr -> children [index];
        }
        else
        {
            curr = NULL;
            return curr;
        }
    }

    return curr;
}

void printSubtree (struct trieNode *curr, string key)
{
    if (curr -> isEnd)
    {
        cout << key << endl;
    }
    else
    {
        for (int i = 0; i < 26; i ++)
        {
            if (curr -> children [i] != NULL)
            {
                char ch = 'a' + i;
                printSubtree (curr -> children [i], key + ch);
            }
        }
    }
}

int printAutoSuggestions (struct trieNode *root, string key)
{
    //2 parts - one to search and one to print the strings
    struct trieNode *lastMatchedNode = search (root, key);
    if (lastMatchedNode == NULL)
    {
        return -1;
    }

    printf ("The suggestions are : \n");

    printSubtree (lastMatchedNode, key);

    return 1;
}

int main ()
{
    struct trieNode *root;

    root = getNode ();

    insert (root, "stock");
    insert (root, "bear");
    insert (root, "bull");
    insert (root, "storm");
    insert (root, "stack");
    insert (root, "rapid");

    int result = printAutoSuggestions (root, "st");

    if (result == -1)
    {
        printf ("No strings with such prefix");
    }

    return 0;
}