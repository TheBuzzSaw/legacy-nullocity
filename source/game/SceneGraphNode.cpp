#include "SceneGraphNode.h"

SceneGraphNode::SceneGraphNode() : mParent(NULL)
{
}

SceneGraphNode::~SceneGraphNode()
{
    for (std::list<SceneGraphNode*>::iterator i = mNodes.begin();
        i != mNodes.end(); ++i)
    {
        SceneGraphNode* sgn = *i;
        delete sgn;
    }
}

void SceneGraphNode::display()
{
}

void SceneGraphNode::addChildNode(SceneGraphNode& inNode)
{
    inNode.mParent = this;
    mNodes.push_back(&inNode);
}

void SceneGraphNode::removeChildNode(SceneGraphNode& inNode)
{
    inNode.mParent = NULL;
    mNodes.remove(&inNode);
}

void SceneGraphNode::removeFromParentNode()
{
    if (mParent) mParent->removeChildNode(*this);
}

void SceneGraphNode::updateMatrices(const CGE::Matrix4x4<float>& inMatrix)
{
    mCompositeTransform.multiply(inMatrix, mTransform);
    for (std::list<SceneGraphNode*>::iterator i = mNodes.begin();
        i != mNodes.end(); ++i)
    {
        SceneGraphNode& sgn = *(*i);
        sgn.updateMatrices(mCompositeTransform);
    }
}
