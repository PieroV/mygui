/*!
	@file
	@author		Albert Semenov
	@date		08/2010
*/
#ifndef __ITEM_HOLDER_H__
#define __ITEM_HOLDER_H__

#include <MyGUI.h>

namespace tools
{

	template <typename T>
	class ItemHolder
	{
	public:
		typedef std::vector<T*> VectorItem;
		typedef MyGUI::Enumerator<VectorItem> EnumeratorItem;

		typedef MyGUI::delegates::CMultiDelegate0 EventHandle_ChangeSelection;

	public:
		ItemHolder() :
			mItemSelected(nullptr)
		{
		}

		virtual ~ItemHolder()
		{
			destroyAllChilds();
		}

		T* createChild()
		{
			T* item = new T();
			mChilds.push_back(item);

			eventChangeList();

			return item;
		}

		void destroyChild(T* _item)
		{
			typename VectorItem::iterator item = std::find(mChilds.begin(), mChilds.end(), _item);
			if (item != mChilds.end())
			{
				if (*item == mItemSelected)
				{
					mItemSelected = nullptr;
					eventChangeSelection();
				}

				delete *item;
				mChilds.erase(item);
			}
			else
			{
				MYGUI_EXCEPT("item not found");
			}

			eventChangeList();
		}

		void destroyAllChilds()
		{
			if (mItemSelected != nullptr)
				setItemSelected(nullptr);

			if (!mChilds.empty())
			{
				for (VectorItem::iterator item=mChilds.begin(); item!=mChilds.end(); ++item)
					delete *item;
				mChilds.clear();

				eventChangeList();
			}
		}

		EnumeratorItem getChildsEnumerator()
		{
			return EnumeratorItem(mChilds);
		}

		T* getItemSelected()
		{
			return mItemSelected;
		}

		void setItemSelected(T* _value)
		{
			mItemSelected = _value;
			eventChangeSelection();
		}

		EventHandle_ChangeSelection eventChangeSelection;
		EventHandle_ChangeSelection eventChangeList;

	private:
		VectorItem mChilds;
		T* mItemSelected;
	};

} // namespace tools

#endif // __ITEM_HOLDER_H__
