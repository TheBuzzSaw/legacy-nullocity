#ifndef SCENEGRAPHNODE_H
#define SCENEGRAPHNODE_H

#include <CGE/Matrix4x4.h>

#include <list>

class SceneGraphNode
{
    public:
        SceneGraphNode();
        virtual ~SceneGraphNode();

        virtual void display();

        void addChildNode(SceneGraphNode& inNode);
        void removeChildNode(SceneGraphNode& inNode);
        void removeFromParentNode();

        void updateMatrices(const CGE::Matrix4x4<float>& inMatrix);

        inline const CGE::Matrix4x4<float>& compositeMatrix() const
        {
            return mCompositeTransform;
        }

    protected:
        CGE::Matrix4x4<float> mTransform;

    private:
        SceneGraphNode* mParent;
        std::list<SceneGraphNode*> mNodes;
        CGE::Matrix4x4<float> mCompositeTransform;
};

#endif
