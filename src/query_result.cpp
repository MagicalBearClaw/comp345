#include "../includes/query_result.h"

query_result::query_result(Index_item idxItem, double score) : idxItem(idxItem), score(score)
{

}

Index_item query_result::getItem() const
{
	return idxItem;
}

double query_result::getScore() const
{
	return score;
}
