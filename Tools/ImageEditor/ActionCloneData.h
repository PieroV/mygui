/*!
	@file
	@author		Albert Semenov
	@date		07/2012
*/

#ifndef _c7757d42_4060_44df_a0c2_06275945b83f_
#define _c7757d42_4060_44df_a0c2_06275945b83f_

#include "Action.h"
#include "Data.h"

namespace tools
{

	class ActionCloneData :
		public Action
	{
	public:
		ActionCloneData();
		virtual ~ActionCloneData();

		virtual void doAction();
		virtual void undoAction();

		void setPrototype(Data* _prototype);
		void setUniqueProperty(const std::string& _value);

	private:
		std::string mType;
		Data* mData;
		Data* mParent;
		Data* mPrototype;
		bool mComplete;
		std::string mUniqueProperty;

		typedef std::pair<Property*, std::string> PairProprty;
		typedef std::vector<PairProprty> VectorPairProperty;
		VectorPairProperty mOldValues;
	};

}

#endif
