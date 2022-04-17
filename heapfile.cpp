/*
 
			उद्यमेन हि सिध्यन्ति कार्याणि न मनोरथैः।
			न हि सुप्तस्य सिंहस्य प्रविशन्ति मुखे मृगा:।।
 
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef vector<int> vi;
typedef vector<vi> vii;
typedef pair<int, int> pii;
typedef vector<pair<int, int>> vpii;
#define sz(a) int((a).size())
#define all(c) (c).begin(), (c).end()
#define rall(x) x.rbegin(), x.rend()
#define ld long double
#define pb push_back
#define sza(x) ((int)x.size())
#define f(i,s,n) for(long long int i=s;i<n;i++)

class Page{
    public:
        int size;
        int count;
        Page *prev; 
        Page *next; 
        int free_space;
        vi data;
        vpii dir;

        Page(int s){
            size = s;
            count=0;
            prev = nullptr;
            next = nullptr;
            free_space = 0;
        }
        int get_free_space(){
            int end = size-16;
            int d = dir.size() * 4;
            return end - d - free_space;
        }
        bool has_free_space(int s){
            return get_free_space() >= s+4;
        }

        void insert(int s,int pk){
            data.push_back(pk);
            dir.push_back({free_space,s});
            free_space += s;
            count++;
        }
};

class HeapFile{
    public:
        Page *root;
        int pageSize;

        HeapFile(int s){
            root = nullptr;
            pageSize = s;
        }

        void insert(int s,int pk){
            if(root == nullptr){
                root = new Page(pageSize);
                root->insert(s,pk);
                return;
            }
            Page *curr;
            curr = root;
            while(curr != nullptr){
                if(curr->has_free_space(s)){
                    curr->insert(s,pk);
                    return;
                }
                if(curr->next == nullptr){
                    curr->next = new Page(pageSize);
                    curr->next->prev = curr;
                    curr->next->insert(s,pk);
                    return;
                }
                curr = curr->next;
            }
        }

        void search(int pk){
            int page_id=0;
            Page *curr;
            curr = root;
            while(curr != nullptr){
                for (int i = 0; i < curr->data.size(); i++){
                    if(curr->data[i]==pk){
                        cout<<page_id<<" "<<i<<"\n";
                        return;
                    }
                }
                curr = curr->next;
                page_id++;
            }
            cout<<"-1 -1\n";
        }

        void status(){
            int page_id=0;
            Page *curr;
            curr = root;
            while(curr != nullptr){
                curr = curr->next;
                page_id++;
            }
            curr = root;
            cout<<page_id<<" ";
            while(curr != nullptr){
                cout<<curr->count<<" ";
                curr = curr->next;
            }
            cout<<endl;
        }
};

int main(){
    int s;
    cin>>s;
    HeapFile *h = new HeapFile(s);
    int n,size,key;
    while (cin >> n) {
        if (n == 1) {
            cin >> size >> key;
            h->insert(size,key);
        } else if (n == 2) {
            h->status();
        } else if (n == 3) {
            cin >> key;
            h->search(key);
        } else {
            return 0;
        }
    }
    return 0;
}