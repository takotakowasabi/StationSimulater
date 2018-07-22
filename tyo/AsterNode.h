#pragma once
#include <memory>
#include <Siv3D.hpp>

enum class NodeStatus {
	none,
	open,
	closed,
};

struct AsterNode;
using spAsterNode = std::shared_ptr<AsterNode>;

struct AsterNode {
	AsterNode(const Vec3& pos) : position(pos), status(NodeStatus::none), blockType(0) {}
	
	const Vec3 position;
	NodeStatus status;
	int trueCost;
	int estimateCost;
	spAsterNode baseNode;
	int blockType;
};

bool operator< (const spAsterNode& lhs, const spAsterNode& rhs);