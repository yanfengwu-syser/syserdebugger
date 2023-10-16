#ifndef _ALT_RANGE_MAP_HPP_
#define _ALT_RANGE_MAP_HPP_

ALT_NAME_SPACE_BEGIN

template<class KEY>
class TRangeKey
{
public:
	KEY		Start;
	KEY		End;
	TRangeKey(const KEY&Key = 0){	Start=End=Key;	}
	TRangeKey(const KEY&StartKey,const KEY&EndKey){	Start=StartKey;	End=EndKey;	}
public:
	const KEY&	operator=(const KEY&Key){return Start = End = Key;}
	bool inline operator==(const KEY& Key)const{ return Key>=Start && Key<=End; }
	bool inline operator!=(const KEY& Key)const{ return Key<Start || Key>End; }
	bool inline operator==(const TRangeKey& RangeKey)const
	{
		if(RangeKey.Start == RangeKey.End)
			return operator==(RangeKey.Start);
		return Start==RangeKey.Start && End==RangeKey.End;
	}
	bool inline operator!=(const TRangeKey& RangeKey)const
	{
		return ! operator==(RangeKey);
	}
	bool inline operator<(const TRangeKey& RangeKey)const
	{
		if(RangeKey.Start == RangeKey.End)
			return End<RangeKey.Start;
		else
			return Start<RangeKey.Start;
	}
};

template<class KEY,class VALUE = ALT_EMPTY_STRUCT>
class TRangeMap : public TMap<TRangeKey<KEY>,VALUE>
{
public:
	typedef TRangeKey<KEY>  RANGE;
};

ALT_NAME_SPACE_END

#endif
