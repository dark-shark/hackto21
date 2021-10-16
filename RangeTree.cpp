#include "RangeTree.h"
#include <iostream>
#include <algorithm>
using namespace std;

template <typename T>
int RangeTree<T>::getHeight(Node<T>* &node){
    if(node) return node->height;
    return -1;
}

template <typename T>
int RangeTree<T>::getBalanceFactor(Node<T>* &node){
    return getHeight(node->left) - getHeight(node->right);
}

template <typename T>
void RangeTree<T>::rotationToLeft(Node<T>* &parent){
    Node<T>* temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    parent = temp;
    parent->left->height = max(getHeight(parent->left->left), getHeight(parent->left->right)) + 1;
    parent->height = max(getHeight(parent->left), getHeight(parent->right)) + 1;
}

template <typename T>
void RangeTree<T>::rotationToRight(Node<T>* &parent){
    Node<T>* temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    parent = temp;
    parent->right->height = max(getHeight(parent->right->left), getHeight(parent->right->right)) + 1;
    parent->height = max(getHeight(parent->left), getHeight(parent->right)) + 1;
}

template <typename T>
void RangeTree<T>::correctBalance(Node<T>* &node) {
    int hb = getBalanceFactor(node);
    if (hb >= 2) {
        if (getBalanceFactor(node->left) >= 1)
            rotationToRight(node);
        else {
            rotationToLeft(node->left);
            rotationToRight(node);
        }
    } else if (hb <= -2) {
        if (getBalanceFactor(node->right) <= -1)
            rotationToLeft(node);
        else {
            rotationToRight(node->right);
            rotationToLeft(node);
        }
    }
}

template<typename T>
void RangeTree<T>::build2DRangeTree(vector<pair<T, T>>& pointSet){
    this->root = build2DRangeTreeUtil(pointSet);
}

template<typename T>
Node<T>* RangeTree<T>::build2DRangeTreeUtil(vector<pair<T, T>>& pointSet){
    if(pointSet.size() == 1){
        Node<T>* leaf = new Node<T>(pointSet[0]);
        return leaf;
    }else{
        RangeTree<T>* treeAssoc = new RangeTree<T>();
        auto rootTreeAssoc = treeAssoc->getRoot();
        for(auto& point : pointSet)
            insert(rootTreeAssoc, point, 2);
        treeAssoc->setRoot(rootTreeAssoc);
        sort(pointSet.begin(), pointSet.end());
        pair<T,T> mid = pointSet[pointSet.size()/2 - 1];
        vector<pair<T,T>> pleft, pright;
        for(auto& point : pointSet){
            if(point <= mid) pleft.push_back(point);
            else pright.push_back(point);
        }
        Node<T>* leftNode = build2DRangeTreeUtil(pleft);
        Node<T>* rightNode = build2DRangeTreeUtil(pright);
        Node<T>* v = new Node<T>(mid);
        v->left = leftNode;
        v->right = rightNode;
        v->treeAssociated = treeAssoc;
        v->height = max(getHeight(v->left), getHeight(v->right)) + 1;
        return v;
    }
}

template<typename T>
Node<T>* RangeTree<T>::findSplitNode(Node<T>* treeRoot, T min, T max, int dimensionNumber){
    Node<T>* temp = treeRoot;
    T value = temp->getDimensionValue(dimensionNumber);
    while(temp->height != 0 and (max <= value || value < min)){
        if(max <= value) temp = temp->left;
        else temp = temp->right;
        value = temp->getDimensionValue(dimensionNumber);
    }
    return temp;
}

template<typename T>
vector<pair<T, T>> RangeTree<T>::rangeQuery1D(Node<T>* treeRoot, T min, T max){
    Node<T>* splitNode = findSplitNode(treeRoot, min, max, 2);
    vector<pair<T, T>> output;
    if(splitNode->height == 0){
        if(min <= splitNode->data.second && splitNode->data.second <= max)
            output.push_back(splitNode->data);
    }else{
        Node<T>* node = splitNode->left;
        while(node->height != 0){
            if(min <= node->data.second){
                vector<pair<T, T>> leaves = reportSubtree(node->right);
                output.insert(output.begin(), leaves.begin(), leaves.end());
                node = node->left;
            }else node = node->right;
        }
        if(min <= node->data.second) output.insert(output.begin(), node->data);

        node = splitNode->right;
        while(node->height != 0){
            if(node->data.second <= max){
                vector<pair<T, T>> leaves = reportSubtree(node->left);
                output.insert(output.end(), leaves.begin(), leaves.end());
                node = node->right;
            }else node = node->left;
        }
        if(node->data.second <= max) output.insert(output.end(), node->data);
    }
    return output;
}

template<typename T>
vector<pair<T, T>> RangeTree<T>::rangeQuery2D(Node<T>* treeRoot, pair<T,T> xrange, pair<T,T> yrange){
    Node<T>* splitNode = findSplitNode(treeRoot, xrange.first, xrange.second, 1);
    vector<pair<T, T>> output;
    if(splitNode->height == 0){
        if(xrange.first <= splitNode->data.first && splitNode->data.first <= xrange.second)
            output.push_back(splitNode->data);
    }else{
        Node<T>* node = splitNode->left;
        while(node->height != 0){
            if(xrange.first <= node->data.first){
                vector<pair<T, T>> leaves = rangeQuery1D(node->right->treeAssociated->getRoot(), yrange.first, yrange.second);
                output.insert(output.begin(), leaves.begin(), leaves.end());
                node = node->left;
            }else node = node->right;
        }
        if(xrange.first <= node->data.first && node->data.first <= xrange.second
            && yrange.first <= node->data.second && node->data.second <= yrange.second) 
            output.insert(output.begin(), node->data);

        node = splitNode->right;
        while(node->height != 0){
            if(node->data.first <= xrange.second){
                vector<pair<T, T>> leaves = rangeQuery1D(node->left->treeAssociated->getRoot(), yrange.first, yrange.second);
                output.insert(output.end(), leaves.begin(), leaves.end());
                node = node->right;
            }else node = node->left;
        }
        if(xrange.first <= node->data.first && node->data.first <= xrange.second
            && yrange.first <= node->data.second && node->data.second <= yrange.second) 
            output.insert(output.begin(), node->data);
    }
    sort(output.begin(), output.end());
    output.erase(unique(output.begin(), output.end()), output.end());
    return output;
}

template <typename T>
vector<pair<T, T>> RangeTree<T>::reportSubtree(Node<T>* node){
    if(node->height == 0){
        return vector<pair<T, T>>(1, node->data);
    }
    vector<pair<T, T>> output;
    vector<pair<T, T>> leaves1 = reportSubtree(node->left);
    vector<pair<T, T>> leaves2 = reportSubtree(node->right);
    output.insert(output.begin(), leaves1.begin(), leaves1.end());
    output.insert(output.end(), leaves2.begin(), leaves2.end());
    return output;
}
template<typename T>
void RangeTree<T>::insert(Node<T>* &node, pair<T,T> value, int dimensionNumber){
    T toCompare = dimensionNumber == 1 ? value.first : value.second;
    if(node == nullptr){
        node = new Node<T>(value);
        return ;
    }
    if(toCompare > node->getDimensionValue(dimensionNumber)){
        if(!node->right){
            node->right = new Node<T>(value);
            node->left = new Node<T>(node->data);
        }else
            insert(node->right, value, dimensionNumber);
    }else{
        if(!node->left){
            node->left = new Node<T>(value, 1);
            node->left->left = new Node<T>(value);
        }else
            insert(node->left, value, dimensionNumber);
    }
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    correctBalance(node);
}



template <typename T>
void RangeTree<T>::printTree(Node<T>* &root, int space){
    if (root == NULL) 
        return;
    space += COUNT;
    printTree(root->right, space);
    cout << endl; 
    for (int i = COUNT; i < space; i++) 
        cout<<" "; 
    cout << "(" << root->data.first << ", "<<root->data.second << ") " << endl;
    printTree(root->left, space); 
} 
