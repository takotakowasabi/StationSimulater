#include "AsterNode.h"

bool operator< (const spAsterNode& lhs, const spAsterNode& rhs) {
 if (lhs->estimateCost + lhs->trueCost == rhs->estimateCost + rhs->trueCost) return lhs->trueCost > rhs->trueCost;
 return lhs->estimateCost + lhs->trueCost > rhs->estimateCost + rhs->trueCost;
}