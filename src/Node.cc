#include "Node.h"

Node::Node(int v, int y)
{
  this->outLength = v;
  this->cordY = y;
  this->distance = 0;
  this->next = NULL;
}

void Node::addNodePointer(Node *n)
{
  this->pointedBy.push_back(n);
}

vector<Node *> Node::getNodePointers()
{
  return this->pointedBy;
}

void Node::setDistance(int d)
{
  this->distance = d;
}

int Node::getDistance()
{
  return this->distance;
}

void Node::setNext(Node *n)
{
  this->next = n;
}

Node *Node::getNext()
{
  return this->next;
}

int Node::getOutLength()
{
  return this->outLength;
}

int Node::getY()
{
  return this->cordY;
}