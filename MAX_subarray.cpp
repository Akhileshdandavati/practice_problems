#include <iostream>
#include <deque> 
#include <algorithm>

using namespace std;

void printKMax(int arr[], int n, int k){
	deque<int> temp;
    
    // Initlize the deque
    for (int i = 0; i < k; ++i) {
        temp.push_back(arr[i]);
    }
    // Find the max and intialize for the first subset
    deque<int>::iterator max = std::max_element(temp.begin(), temp.end());
    cout << *max<< " ";

    for (int i = 1; i <= n - k; ++i) {
        // If the max value is at the beginning of deque, find max again
        if (max == temp.begin()){
            temp.pop_front();
            temp.push_back(arr[i+k-1]);
            max = std::max_element(temp.begin(), temp.end());
        // If not compare with new value and set the new max pointer
        } else {
            temp.push_back(arr[i+k-1]);
            if (temp.back() >= *max) max = temp.end()-1;
            temp.pop_front();
        }
        cout << *max << " ";
    }
    cout << endl;
}

int main(){
  
	int t;
	cin >> t;
	while(t>0) {
		int n,k;
    	cin >> n >> k;
    	int i;
    	int arr[n];
    	for(i=0;i<n;i++)
      		cin >> arr[i];
    	printKMax(arr, n, k);
    	t--;
  	}
  	return 0;
}