#pragma once

namespace mds
{
	template <typename T>
	class FixedStack
	{
	public:
		inline FixedStack(size_t elementCount)
			: mCapacity(elementCount)
			, mElementCount(0)
		{
			mDatas = new T[elementCount];
		}

		inline ~FixedStack()
		{
			delete[] mDatas;
		}

#pragma warning(push)
#pragma warning(disable: 6011)
		inline T& top()
		{
			if (mElementCount == 0)
			{
				char* np = 0x00;

				*np = 1;
			}

			return mDatas[mElementCount - 1];
		}
#pragma warning(pop)

		inline void push(T data)
		{
			if (mCapacity == mElementCount)
			{
				return;
			}

			mDatas[mElementCount] = data;
			++mElementCount;
		}

		inline void pop()
		{
			mElementCount = mElementCount > 0 ? mElementCount - 1 : 0;
		}

		inline bool empty()
		{
			return mElementCount == 0;
		}

		inline size_t size()
		{
			return mElementCount;
		}

	private:
		T* mDatas;
		size_t mCapacity;
		size_t mElementCount;
	};
}
