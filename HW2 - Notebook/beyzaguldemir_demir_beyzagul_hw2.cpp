#include <iostream>
#include "binary_search_tree.cpp"
#include "avl_tree.cpp"
#include <string>
#include <fstream>
#include <chrono>

using namespace std;

struct Item { 

	string title;
	string info;

	Item() {}

	bool operator > (const Item & rhs) const {
		if (this->title > rhs.title)
			return true;
		return false;
	}

	bool operator < (const Item & rhs) const {
		if (this->title < rhs.title)
			return true;
		return false;
	}
};

template <class Type>
struct Section { 
	string title;
	Type tree;

	bool operator > (const Section<Type>& rhs) const {
		if (this->title > rhs.title)
            return true;
        return false;
	}

	bool operator < (const Section<Type>& rhs) const {
		if (this->title < rhs.title)
            return true;
        return false;
	}

	const Section<Type>& operator=(const Section<Type>& rhs) {
		title = rhs.title;
		tree = rhs.tree;
		return *this;
	}
};

ostream & operator << (ostream & os, const Item & i) {
	os << i.title;
	return os;
}

ostream & operator << (ostream & os, const Section<BinarySearchTree<Item>> & s) {
	os << s.title;
	return os;
}

ostream & operator << (ostream & os, const Section<AvlTree<Item>> & s) {
	os << s.title;
	return os;
}

template <class Type>
void printTree(const Type & tree) {
    
	string myLine = "*****";
	cout << endl << myLine << endl;
	if (!tree.isEmpty()) {
		tree.printTree();
	}
	cout << myLine << endl;
}

bool sectionExists(const BinarySearchTree<Section<BinarySearchTree<Item>>>& notebookBST,
                   const AvlTree<Section<AvlTree<Item>>>& notebookAVL,
                   string sectionTitle)
{
	Section<AvlTree<Item>> sectionAvl;
	sectionAvl.title = sectionTitle;
	Section<BinarySearchTree<Item>> sectionBST;
	sectionBST.title = sectionTitle;
    int avl_section_title_length = notebookAVL.find(sectionAvl).title.length();
    int bst_section_title_length = notebookBST.find(sectionBST).title.length();  
	if ( avl_section_title_length != 0){
		if (bst_section_title_length != 0)
			return true;
	}
	return false;
}
void printTimeBST(long long BSTtime) {
	cout << "[BST] Elapsed time: " << BSTtime << " microseconds" << endl;
}

void printTimeAVL(long long AVLtime) {
	cout << "[AVL] Elapsed time: " << AVLtime << " microseconds" << endl;
}

void implementInput5(BinarySearchTree<Section<BinarySearchTree<Item>>>& notebookBST, AvlTree<Section<AvlTree<Item>>>& notebookAVL) {
	string SecTitle;
	cout << "Enter a title for the section: ";
	getline(cin, SecTitle);

	if (sectionExists(notebookBST, notebookAVL, SecTitle)) {
		Section<AvlTree<Item>> sectionAVL;
		sectionAVL.title = SecTitle;
		notebookAVL.remove(sectionAVL);
		Section<BinarySearchTree<Item>> sectionBST;
		sectionBST.title = SecTitle;
		notebookBST.remove(sectionBST);
		cout << "The section has been deleted." << endl;				
	}
	else {
		cout << "Section \"" << SecTitle << "\" does not exist." << endl;

	}
}

void implementInput4(BinarySearchTree<Section<BinarySearchTree<Item>>>& notebookBST, AvlTree<Section<AvlTree<Item>>>& notebookAVL) {
	string SecTitle;
	cout << "Enter a title for the section: ";
	getline(cin, SecTitle);

	if (sectionExists(notebookBST, notebookAVL, SecTitle)) {
		cout << "Section \"" << SecTitle << "\" already exists." << endl;
	}

	else {
		Section<AvlTree<Item>> sectionAVL;
		sectionAVL.title = SecTitle;
		notebookAVL.insert(sectionAVL);
		Section<BinarySearchTree<Item>> sectionBST;
		sectionBST.title = SecTitle;
		notebookBST.insert(sectionBST);
		cout << "The new section \"" << SecTitle << "\" has been inserted." << endl;				
	}
}

void implementInput3(BinarySearchTree<Section<BinarySearchTree<Item>>>& notebookBST,
                   AvlTree<Section<AvlTree<Item>>>& notebookAVL) 
{ // 3 - Select a Section
	string SecTitle;
	cout << "Enter the title of the section: ";
	getline(cin, SecTitle);

	Section<AvlTree<Item>> sectionAVL;
	sectionAVL.title = SecTitle;
	Section<AvlTree<Item>> selectedSectionAVL = notebookAVL.find(sectionAVL);

	Section<BinarySearchTree<Item>> sectionBST;
	sectionBST.title = SecTitle;
	Section<BinarySearchTree<Item>> selectedSectionBST = notebookBST.find(sectionBST);

	int avl_title = selectedSectionAVL.title.length();
	int bst_title = selectedSectionBST.title.length();
	if (avl_title != 0 && bst_title != 0) { 
		string sectionInput;
		cout << endl << "Selected section -> " << SecTitle << endl << 
		"Please enter an input between [1 - 7]:" << endl << 
		"1 - Display the items [AVL]" << endl << 
		"2 - Display the items [BST]" << endl << 
		"3 - Display the information of a item" << endl << 
		"4 - Add new item" << endl << 
		"5 - Update the information of a item" << endl << 
		"6 - Delete an item" << endl << 
		"7 - Return to main menu" << endl;
		cout << "Input: ";
		cin >> sectionInput;
		cin.ignore();

		while (sectionInput != "7") {
			if (sectionInput == "1") { // Display the Items (AVL) 
				printTree(selectedSectionAVL.tree);
			}

			else if (sectionInput == "2") { //Display the Items (BST)
				printTree(selectedSectionBST.tree);
			}

			else if (sectionInput == "3") { //Display the information of an Item
				string itemTitleInput;
				cout << "Enter the title of the item: ";
				getline(cin, itemTitleInput);
						
				Item searched, Item_AVL, Item_BST;
				searched.title = itemTitleInput;

				/******************** AVL ELAPSED TIME CALCULATE ****************************/
				auto AVLstart = std::chrono::high_resolution_clock::now();
				Item_AVL = selectedSectionAVL.tree.find(searched);
				auto AVLend = std::chrono::high_resolution_clock::now();
				long long AVLtime = (AVLend - AVLstart).count() / 1000.0;
				printTimeAVL(AVLtime);

				/******************** BST ELAPSED TIME CALCULATE ****************************/
				auto BSTstart = std::chrono::high_resolution_clock::now();
				Item_BST = selectedSectionBST.tree.find(searched);
				auto BSTend = std::chrono::high_resolution_clock::now();
				long long BSTtime = (BSTend - BSTstart).count() / 1000.0;
				printTimeBST(BSTtime);

				if (!(Item_AVL.title.length() != 0 && Item_BST.title.length() != 0 && Item_AVL.info == Item_BST.info)) { // If the Item DOES exist and info's match
					cout << "Invalid title." << endl;			
				}

				else { 
					cout << Item_AVL.info << endl;
				}
			}

			else if (sectionInput == "4") { //Add a new Item
				string itemTitleInput;
				cout << "Enter the title of the item: ";
				getline(cin, itemTitleInput);

				Item searched, Item_AVL, Item_BST;
				searched.title = itemTitleInput;
				/******************** AVL ELAPSED TIME CALCULATE ****************************/
				auto AVLstart = std::chrono::high_resolution_clock::now();
				Item_AVL = selectedSectionAVL.tree.find(searched);
				auto AVLend = std::chrono::high_resolution_clock::now();
				long long AVLtime = (AVLend - AVLstart).count() / 1000.0;

				/******************** BST ELAPSED TIME CALCULATE ****************************/
				auto BSTstart = std::chrono::high_resolution_clock::now();
				Item_BST = selectedSectionBST.tree.find(searched);
				auto BSTend = std::chrono::high_resolution_clock::now();
				long long BSTtime = (BSTend - BSTstart).count() / 1000.0;

				if (Item_AVL.title.length() != 0 && Item_BST.title.length() != 0) { // If the Item with the given title already exists
					cout << "Item \"" << itemTitleInput << "\" already exists in the \"" << selectedSectionAVL.title << "\"." << endl;
				}

				else { 
					string inputItemInfo;
					cout << "Enter a description for the item: ";
					getline(cin, inputItemInfo);


					Item itemToBeInserted;
					itemToBeInserted.title = itemTitleInput;
					itemToBeInserted.info = inputItemInfo;

					Section<BinarySearchTree<Item>> section_BST;
					section_BST.title = SecTitle;

					Section<AvlTree<Item>> section_AVL;
					section_AVL.title = SecTitle;

					/******************** AVL ELAPSED TIME CALCULATE ****************************/
					auto startAVL2 = std::chrono::high_resolution_clock::now();
					selectedSectionAVL.tree.insert(itemToBeInserted);
					notebookAVL.Find_Update(section_AVL, selectedSectionAVL);
					auto endAVL2 = std::chrono::high_resolution_clock::now();

					AVLtime = AVLtime + (endAVL2 - startAVL2).count() / 1000.00;
					printTimeAVL(AVLtime);
                            
					/******************** BST ELAPSED TIME CALCULATE ******************************/
					auto startBST2 = std::chrono::high_resolution_clock::now();
					selectedSectionBST.tree.insert(itemToBeInserted);
					notebookBST.Find_Update(section_BST, selectedSectionBST);
					auto endBST2 = std::chrono::high_resolution_clock::now();

					BSTtime = BSTtime + (endBST2 - startBST2).count() / 1000.0;
					printTimeBST(BSTtime);
							

					cout << "The new item \"" << itemTitleInput << "\" has been inserted." << endl;
				}
			}

			else if (sectionInput == "5") { // Update the information of an Item
				string itemTitleInput;
				cout << "Enter the title of the item: ";
				getline(cin, itemTitleInput);

				Item searched, Item_AVL, Item_BST;
				searched.title = itemTitleInput;

				/******************** AVL ELAPSED TIME CALCULATE ******************************/
				auto AVLstart = std::chrono::high_resolution_clock::now();
				Item_AVL = selectedSectionAVL.tree.find(searched);
				auto AVLend = std::chrono::high_resolution_clock::now();
				long long AVLtime = (AVLend - AVLstart).count() / 1000.0;
				printTimeAVL(AVLtime);

				/******************** BST ELAPSED TIME CALCULATE ******************************/
				auto BSTstart = std::chrono::high_resolution_clock::now();
				Item_BST = selectedSectionBST.tree.find(searched);
				auto BSTend = std::chrono::high_resolution_clock::now();
				long long BSTtime = (BSTend - BSTstart).count() / 1000.0;
				printTimeBST(BSTtime);

				if (Item_AVL.title.length() != 0 && Item_BST.title.length() != 0) { 
					string inputItemInfo;
					cout << "Enter the new information: ";
					getline(cin, inputItemInfo);

					Item toBeFound;
					toBeFound.title = itemTitleInput;
					Item updated;
					updated.title = itemTitleInput;
					updated.info = inputItemInfo;

					Section<BinarySearchTree<Item>> section_BST;
					section_BST.title = SecTitle;
					selectedSectionBST.tree.Find_Update(toBeFound, updated);

					Section<AvlTree<Item>> section_AVL;
					section_AVL.title = SecTitle;
					selectedSectionAVL.tree.Find_Update(toBeFound, updated);

					notebookBST.Find_Update(section_BST, selectedSectionBST);
					notebookAVL.Find_Update(section_AVL, selectedSectionAVL);

					cout << "The content " << itemTitleInput << " has been updated." << endl;
				}

				else { 
					cout << "Item \"" << itemTitleInput << "\" does not exist in the \"" << selectedSectionAVL.title << "\"." << endl;
				}
			}

			else if (sectionInput == "6") { // Delete an Item

				string itemTitleInput;
				cout << "Enter the title of the item: ";
				getline(cin, itemTitleInput);


				Item searched, Item_AVL, Item_BST;
				searched.title = itemTitleInput;

				/******************** AVL ELAPSED TIME CALCULATE ****************************/
				auto AVLstart = std::chrono::high_resolution_clock::now();
				Item_AVL = selectedSectionAVL.tree.find(searched);
				auto AVLend = std::chrono::high_resolution_clock::now();
				long long AVLtime = (AVLend - AVLstart).count() / 1000.0;

					/******************** BST ELAPSED TIME CALCULATE ****************************/
				auto BSTstart = std::chrono::high_resolution_clock::now();
				Item_BST = selectedSectionBST.tree.find(searched);
				auto BSTend = std::chrono::high_resolution_clock::now();
				long long BSTtime = (BSTend - BSTstart).count() / 1000.0;

				if (Item_AVL.title.length() != 0 || Item_BST.title.length() != 0) { 
					Item itemToBeRemoved;
					itemToBeRemoved.title = itemTitleInput;

					Section<BinarySearchTree<Item>> section_BST;
					section_BST.title = SecTitle;

					Section<AvlTree<Item>> section_AVL;
					section_AVL.title = SecTitle;

					/******************** AVL ELAPSED TIME CALCULATE ****************************/
					auto startAVL2 = std::chrono::high_resolution_clock::now();
					selectedSectionAVL.tree.remove(itemToBeRemoved);
					notebookAVL.Find_Update(section_AVL, selectedSectionAVL);
					auto endAVL2 = std::chrono::high_resolution_clock::now();

					AVLtime = AVLtime + (endAVL2 - startAVL2).count() / 1000.0;
					printTimeAVL(AVLtime);
							
					/******************** BST ELAPSED TIME CALCULATE ****************************/
					auto startBST2 = std::chrono::high_resolution_clock::now();
					selectedSectionBST.tree.remove(itemToBeRemoved);
					notebookBST.Find_Update(section_BST, selectedSectionBST);
					auto endBST2 = std::chrono::high_resolution_clock::now();

					BSTtime = BSTtime + (endBST2 - startBST2).count() / 1000.0;
					printTimeBST(BSTtime);

					cout << "The item \"" << itemTitleInput << "\" has been deleted." << endl;			
				}

				else { 
					cout << "Item \"" << itemTitleInput << "\" does not exist in the \"" << selectedSectionAVL.title << "\"." << endl;
							
				}
			}

			cout << endl << "Input: ";
			cin >> sectionInput;
			cin.ignore();
		}

		if (sectionInput == "7") { 
			cout << endl;
			cout << 
			"MENU\nPlease enter an input between [1 - 6]:" << endl << 
			"1 - Display the sections [AVL]" << endl << 
			"2 - Display the sections [BST]" << endl << 
			"3 - Select a section" << endl << 
			"4 - Add new section" << endl << 
			"5 - Delete a section" << endl << 
			"6 - Exit";
		}
	}

	else {
		cout << "Invalid title!" << endl;
	}

}


int main() {
	cout << "Welcome to the Notebook!" << endl << endl;
	
	BinarySearchTree<Section<BinarySearchTree<Item>>> notebookBST;
    AvlTree<Section<AvlTree<Item>>> notebookAVL;

	string filename = "data.txt";
	ifstream input;
	input.open(filename.c_str());

	if (input.fail()) {
		cout << "ERROR: File named " << filename << " cannot be opened." << endl;
	}

	else {
		string line;
		getline(input, line);
		Section<BinarySearchTree<Item>> currSecBST;
		currSecBST.title = line;
		Section<AvlTree<Item>> currSecAVL;
		currSecAVL.title = line;

		long long AVLtime = 0, BSTtime = 0;

		//read line by line and create tree
		while (getline(input, line)) { 
			if (line.at(0) != '-') {  

				/******************** AVL ELAPSED TIME CALCULATE ****************************/
				auto AVLstart = std::chrono::high_resolution_clock::now();
				notebookAVL.insert(currSecAVL);
				auto AVLend = std::chrono::high_resolution_clock::now();
				AVLtime = AVLtime + (AVLend - AVLstart).count() / 1000.0;
				cout << "Section \"" << currSecAVL.title << "\" has been inserted into the AVL notebook." << endl;
				printTimeAVL(AVLtime);
				AVLtime = 0; 
				currSecAVL.title = line;

				/******************** BST ELAPSED TIME CALCULATE ****************************/
				auto BSTstart = std::chrono::high_resolution_clock::now();
				notebookBST.insert(currSecBST); 
				auto BSTend = std::chrono::high_resolution_clock::now();

				BSTtime = BSTtime + (BSTend - BSTstart).count() / 1000.0;
				cout << "Section \"" << currSecBST.title << "\" has been inserted into the BST notebook." << endl;
				printTimeBST(BSTtime);

				BSTtime = 0; 
				currSecBST.title = line;
				cout << endl;
			}

			else { 
				int seperator = line.find('-', 1);


				Item tobeInsertedAVL;
				string Item_title_AVL = line.substr(1, seperator - 1);
				string Item_info_AVL = line.substr(seperator + 1);
				tobeInsertedAVL.title = Item_title_AVL;
				tobeInsertedAVL.info = Item_info_AVL;
			    /******************** AVL ELAPSED TIME CALCULATE ****************************/
				auto AVLstart = std::chrono::high_resolution_clock::now();
				currSecAVL.tree.insert(tobeInsertedAVL); 
				auto AVLend = std::chrono::high_resolution_clock::now();
				AVLtime += (AVLend - AVLstart).count() / 1000.0; // 


				Item tobeInsertedBST;
				string Item_title_BST = line.substr(1, seperator - 1);
				string Item_info_BST = line.substr(seperator + 1);
				tobeInsertedBST.title = Item_title_BST;
				tobeInsertedBST.info = Item_info_BST;
				/******************** BST ELAPSED TIME CALCULATE ****************************/
				auto BSTstart = std::chrono::high_resolution_clock::now();
				currSecBST.tree.insert(tobeInsertedBST);
				auto BSTend = std::chrono::high_resolution_clock::now();
				BSTtime += (BSTend - BSTstart).count() / 1000.0; 
			}
		}

		//insert last section
		/******************** AVL ELAPSED TIME CALCULATE ****************************/
		auto AVLstart = std::chrono::high_resolution_clock::now();
		notebookAVL.insert(currSecAVL); 
		auto AVLend = std::chrono::high_resolution_clock::now();

		AVLtime += (AVLend - AVLstart).count() / 1000.0;
		cout << "Section \"" << currSecAVL.title << "\" has been inserted into the AVL notebook." << endl;
		printTimeAVL(AVLtime);

		/******************** BST ELAPSED TIME CALCULATE ****************************/
		auto BSTstart = std::chrono::high_resolution_clock::now();
		notebookBST.insert(currSecBST); 
		auto BSTend = std::chrono::high_resolution_clock::now();

		BSTtime += (BSTend - BSTstart).count() / 1000.0;
		cout << "Section \"" << currSecBST.title << "\" has been inserted into the BST notebook." << endl;
		printTimeBST(BSTtime);

		input.close();
    }

	// until now, we have read "data.txt" and create the tress.
	//From now on, we will implement operations.
	string Input;
	//Section operations
	cout << "MENU\nPlease enter an input between [1 - 6]:" << endl << 
    "1 - Display the sections [AVL]" << endl << 
    "2 - Display the sections [BST]" << endl << 
    "3 - Select a section" << endl << 
    "4 - Add new section" << endl << 
    "5 - Delete a section" << endl << 
    "6 - Exit";
	cout << endl << "Input: ";
	cin >> Input;
	cin.ignore();

	while (Input != "6") {
		if (Input == "5") // Delete a section
			implementInput5(notebookBST, notebookAVL);

		else if (Input == "4")  // Add new Section
			implementInput4(notebookBST, notebookAVL);

		else if (Input == "3")  // Select a Section
			implementInput3(notebookBST, notebookAVL);

		else if (Input == "2")  // Display the Sections (BST)
			printTree(notebookBST);

		else if (Input == "1")  // Display the Sections (AVL)
			printTree(notebookAVL);

		cout << endl << "Input: ";
		cin >> Input;
		cin.ignore();
	}
	return 0;
}

