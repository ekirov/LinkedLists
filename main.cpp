#include <iostream>
#include <string>
#include <map>
#include <cmath>
#include <vector>
using namespace std;


class SinglyLinkedListNode{
public:
	int data;
	SinglyLinkedListNode *next;

	SinglyLinkedListNode(int node_data){
		this->data = node_data;
		this->next = nullptr;
	}
};

class SinglyLinkedList{
	public:
		SinglyLinkedListNode *head;
		SinglyLinkedListNode *tail;

		SinglyLinkedList(){
			this->head = nullptr;
			this->tail = nullptr;
		}

		void insert_node(int node_data){
			SinglyLinkedListNode *node = new SinglyLinkedListNode(node_data);

			if (!this->head){
				this->head = node;
			}
			else {
				this->tail->next = node;
			}
			this->tail = node;
		}

};

void print_singly_linked_list(SinglyLinkedListNode *node){
	while (node){
		cout << node->data;
		node = node->next;
		if (node){
			cout << "->";
		}
	}
}

void free_singly_linked_list(SinglyLinkedListNode* node){
	while (node){
		SinglyLinkedListNode* temp = node;
		node = node->next;
		free(temp);
	}
}

//write code to remove duplicates from an unsorted linked list.
void removeDups(SinglyLinkedListNode* node){
	map<int, int> nodemap;
	map<int, int>::iterator it;
	SinglyLinkedListNode* prev = node;
	nodemap[prev->data] = 1;
	node = node->next;
	while (node){
		it = nodemap.find(node->data);
		if (it != nodemap.end())//we have found a duplicate
		{
			SinglyLinkedListNode* temp = node;
			prev->next = node->next;
			node = node->next;
			free(temp);
		}
		else{
			nodemap[node->data] = 1;
			prev = node;
			node = node->next;
		}
	}
}

//return the kth to last element
// recursive solution
// the length of the list is not known
SinglyLinkedListNode* kthToLast(SinglyLinkedListNode* head, int k, int& i){
	if (head == nullptr){
		return nullptr;
	}
	SinglyLinkedListNode* cur = kthToLast(head->next, k, i);
	i += 1;
	if (i == k)
		return head;
	return cur;
}

SinglyLinkedListNode* kthToLast(SinglyLinkedListNode* head, int k){
	int i = 0;
	return kthToLast(head, k, i);
}

// iterative solution to kth to last problem
// use two pointers with the first one starting at the head and the second starting at head + n, then have both pointers iterate through linked list until second is at the end.
SinglyLinkedListNode* nthToLast(SinglyLinkedListNode* head, int k){
	SinglyLinkedListNode* p1 = head;
	SinglyLinkedListNode* p2 = head;

	for (int i = 0; i < k; i++){
		if (p2->next != nullptr)
			p2 = p2->next;
		else
			return false;
	}
	while (p2 != nullptr){
		p1 = p1->next;
		p2 = p2->next;
	}
	return p1;
}

//adds the elements of two linked lists where the head is the ones place and the next elements are the tens, hundreds, etc.
//page 215
SinglyLinkedListNode* sumLists(SinglyLinkedListNode* h1, SinglyLinkedListNode* h2){
	SinglyLinkedList* sum = new SinglyLinkedList();
	int count = 0;
	int h1_d = 0;
	int h2_d = 0;
	int i_sum = 0;
	while (h1 || h2){
		if (h1)
			h1_d = h1->data;
		else
			h1_d = 0;
		if (h2)
			h2_d = h2->data;
		else
			h2_d = 0;
		h1_d = h1_d*pow(10, count);
		h2_d = h2_d*pow(10, count);
		i_sum += h1_d + h2_d;
		if (h1)
			h1 = h1->next;
		if (h2)
			h2 = h2->next;
		count++;
	}
	string s_sum = to_string(i_sum);
	for (int i = 0; i < s_sum.length(); i++){
		sum->insert_node(s_sum[i]-'0');
	}
	return sum->head;
}



//remove a node from a linked list given only the linkedlistnode and not the head or tail of the linked list
bool deleteNode(SinglyLinkedListNode* del){
	if (del == nullptr)
		return false;
	SinglyLinkedListNode* next = del->next;
	del->data = next->data;
	del->next = next->next;
	free(next);
}


//create a new linkedlist where the nodes less than the partition come to the left of the nodes greater than the partition
//loop through the initial linkedlist and add elements less than the partition to the head of new linkedlist and elements greater than the partition to the tail
SinglyLinkedList* partition(SinglyLinkedList* l, int p){
	SinglyLinkedList* l2 = new SinglyLinkedList();
	SinglyLinkedListNode *cur = l->head;
	l2->head = cur;
	l2->tail = cur;
	cur = cur->next;
	while (cur != nullptr){
		SinglyLinkedListNode* next = cur->next;
		if (cur->data < p){
			cur->next = l2->head;
			l2->head = cur;
		}
		else{
			l2->tail->next = cur;
			l2->tail = cur;
		}
		cur = next;
	}
	cur->next = nullptr;
	return l2;
}

// checks to see whether a linked list is a palindrome by using a slow and fast pointer
bool isPalindrome(SinglyLinkedList* l){
	SinglyLinkedListNode* p1 = l->head;
	SinglyLinkedListNode* p2 = l->head;

	vector<int> stack;
	while (p2 != NULL && p2->next != nullptr){
		stack.push_back(p1->data);
		p1 = p1->next;
		p2 = p2->next->next;
	}
	if (p2){
		p1 = p1->next; //in case length is odd then skip past the middle element
	}

	while (p1){
		int top = stack.back();
		stack.pop_back();
		if (top != p1->data)
			return false;
		p1 = p1->next;
	}
	return true;

}

//find the node that intersects two lists
//find the lengths of each list
//then start at the head of the smaller list and the offset position on the longer list then loop through until the nodes are equal
/*
SinglyLinkedListNode* intersectingNode(SinglyLinkedList* l1, SinglyLinkedList* l2){
	SinglyLinkedListNode* cur1 = l1->head;
	SinglyLinkedListNode* cur2 = l2->head;
	int len_l1 = 0;
	int len_l2 = 0;
	while (cur1){
		len_l1 += 1;
		cur1 = cur1->next;
	}
	while (cur2){
		len_l2 += 1;
		cur2 = cur2->next;
	}


}
*/

SinglyLinkedListNode *multiplyListsSimple(SinglyLinkedListNode *h1, SinglyLinkedListNode *h2){
	int n1 = 0;
	int n2 = 0;
	while (h1 || h2){
		if (h1){
			n1 = n1 * 10 + h1->data;
			h1 = h1->next;
		}
		if (h2){
			n2 = n2 * 10 + h2->data;
			h2 = h2->next;
		}
	}
	int product = n1*n2;
	string product_str = to_string(product);
	SinglyLinkedList *result = new SinglyLinkedList();
	for (int i = 0; i < product_str.length(); i++){
		result->insert_node(product_str[i] - '0');
	}

	return result->head;
	
}

///////////////////////////////////////////////////////////////////////////

/*
much like the multiplyHelper method we use recursion to go from the ones digit back to the last digits
*/
SinglyLinkedListNode *addListsOfSameSize(SinglyLinkedListNode *h1, SinglyLinkedListNode *h2, int &carry){
	if (!h1)
		return nullptr;
	int sum = 0;
	SinglyLinkedListNode *result = new SinglyLinkedListNode(NULL);
	result->next = addListsOfSameSize(h1->next, h2->next, carry);
	sum = h1->data + h2->data + carry;
	carry = sum / 10;
	sum = sum % 10;
	result->data = sum;
	return result;
}

/*
add the remaining digits that were extra on the number with the greatest linked list length/size
*/
SinglyLinkedListNode *addCarry(SinglyLinkedListNode *h1, SinglyLinkedListNode *cur, int &carry, SinglyLinkedListNode *&result){
	int sum = 0;
	if (h1 != cur){
		addCarry(h1->next, cur, carry, result);
		sum = h1->data + carry;
		carry = sum / 10;
		sum = sum % 10;
		SinglyLinkedListNode *temp = new SinglyLinkedListNode(sum);
		temp->next = result;
		return temp;
	}
}

/*
returns a linked list to represent the sum of two other linked lists
ex:
1->2->3 + 3->5 = 123 + 35 = 158 = 1->5->8
*/
SinglyLinkedListNode *addLists(SinglyLinkedListNode *h1, SinglyLinkedListNode *h2)
{
	SinglyLinkedListNode *result = new SinglyLinkedListNode(NULL);
	SinglyLinkedListNode *temp = h1;
	//find the sizes of both lists
	int size1 = 0;
	int size2 = 0;
	while (temp){
		size1++;
		temp = temp->next;
	}
	temp = h2;
	while (temp){
		size2++;
		temp = temp->next;
	}
	int carry = 0;
	if (size1 == size2){ //if both the sizes are the same simply add the lists 
		result = addListsOfSameSize(h1, h2, carry);
	}
	else{ //if the sizes are different we must do some shifting of the pointer to the list of greatest length
		//we want h1 to be the list of greatest length
		if (size2 > size1){
			SinglyLinkedListNode *temp = h1;
			h1 = h2;
			h2 = temp;
			int tempsize = size1;
			size1 = size2;
			size2 = tempsize;
		}
		int diff = size1 - size2;
		SinglyLinkedListNode *cur = h1;
		//shift the greatest length list
		for (int i = 0; i < diff; i++){
			cur = cur->next;
		}
		result = addListsOfSameSize(cur, h2, carry);

		result = addCarry(h1, cur, carry, result);
	}
	//if any carry leftover from adding the carry then add the carry
	if (carry){
		SinglyLinkedListNode *temp = new SinglyLinkedListNode(carry);
		temp->next = result;
		return temp;
	}
	return result;

}

/*
Here is where the actual multiplication occurs
again recursion is used to go to the ones digit and then back to the last digit recursively
*/
SinglyLinkedListNode *multiplyHelper(SinglyLinkedListNode *cur1, int val, int &carry){
	if (!cur1)
		return nullptr;
	SinglyLinkedListNode *result = new SinglyLinkedListNode(NULL);
	result->next = multiplyHelper(cur1->next, val, carry);
	int multiply = cur1->data * val + carry;
	carry = multiply / 10;
	int leftover = multiply % 10;
	result->data = leftover;
	return result;
}

SinglyLinkedListNode *multiplyLists(SinglyLinkedListNode *h1, SinglyLinkedListNode *h2, vector<SinglyLinkedListNode *> &products){
	if (!h2)
		return nullptr;
	SinglyLinkedListNode *result = new SinglyLinkedListNode(NULL);
	/*
	move one of the digits of one of the lists all the way to the ones place
	then recurse back to the tens, hundreds, etc
	*/
	result->next = multiplyLists(h1, h2->next, products);
	int carry = 0;
	/*
	multiply one digit of one of the numbers by the other number to create a product
	*/
	result->next = multiplyHelper(h1, h2->data, carry);
	//insert the remaining carry and/or push back the product to the vector of products
	if (carry != 0){
		result->data = carry;
		products.push_back(result);
	}
	else
		products.push_back(result->next);

	return result;

}

/*
multiplies two linked lists that are representative of a number
ex:
2->5->5 * 1->2->5 = 255 * 125 = 31875 = 3->1->8->7->5
*/
SinglyLinkedListNode *multiplyLists(SinglyLinkedListNode *h1, SinglyLinkedListNode *h2){
	if (!h1)
		return nullptr;
	if (!h2)
		return nullptr;
	vector<SinglyLinkedListNode *> products;
	multiplyLists(h1, h2, products);
	/*
	if only one product then return the answer
	*/
	if (products.size() == 1)
		return products[0];
	int count = 1;
	/*
	we must add trailing zeros to the products except for the first one to represent how multiplication is actually done
	*/
	for (int i = 1; i < products.size(); i++){
		SinglyLinkedListNode *cur = products[i];
		while (cur->next){
			cur = cur->next;
		}
		for (int j = 0; j < count; j++){
			SinglyLinkedListNode *zero = new SinglyLinkedListNode(0);
			cur->next = zero;
			cur = cur->next;
		}
		count++;
	}
	/*
	add the products together to get the final product
	*/
	SinglyLinkedListNode *sum = addLists(products[0], products[1]);
	for (int i = 2; i < products.size(); i++){
		sum = addLists(sum, products[i]);
	}
	return sum;

}

int main(){
	SinglyLinkedList *ll1 = new SinglyLinkedList();
	SinglyLinkedList *ll2 = new SinglyLinkedList();
	ll1->insert_node(2);
	ll1->insert_node(5);
	ll1->insert_node(5);
	ll2->insert_node(1);
	ll2->insert_node(2);
	ll2->insert_node(5);
	SinglyLinkedListNode *product = multiplyLists(ll1->head, ll2->head);
	print_singly_linked_list(product);
	//isPalindrome(ll1);
	//removeDups(llist->head);
	//SinglyLinkedListNode* k2l = kthToLast(llist->head, 5);
	//cout << k2l->data;
	//SinglyLinkedListNode* sum = sumLists(ll1->head, ll2->head);
	//print_singly_linked_list(sum);
	return 0;
}




