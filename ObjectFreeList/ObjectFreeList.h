// version 1.0.0
#pragma once

template <typename T>
class ObjectFreeList
{
private:
	template <typename T>
	struct Node
	{
		T data;
		Node<T>* next;
	};
public:
	ObjectFreeList() = default;

	ObjectFreeList(int capacity)
		: mCapacity(capacity)
		, mSize(capacity)
	{
		Node<T>* nextNode = nullptr;
		for (int i = 0; i < capacity; ++i)
		{
			Node<T>* newNode = new Node<T>;
			newNode->next = nextNode;
			nextNode = newNode;
		}
		head = nextNode;
	}

	int GetCapacity()
	{
		return mCapacity;
	}

	int GetSize()
	{
		return mSize;
	}

	T Alloc()
	{
		Node<T>* ret;

		if (mSize == 0)
		{
			ret = new Node<T>;
			mCapacity++;
		}
		else
		{
			ret = head;
			head = head->next;
			mSize--;
		}

		return reinterpret_cast<T>(ret);
	}

	void Free(T data)
	{
		Node<T>* node = reinterpret_cast<Node<T>*>(data);
		node->next = head;
		head = node;
		mSize++;
	}
private:
	Node<T>* head = nullptr;
	int mCapacity = 0;
	int mSize = 0;
};
