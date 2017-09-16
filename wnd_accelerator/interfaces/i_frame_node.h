#pragma once
#include "afx.h"

#include <functional>
#include <list>

namespace wnd_accelerator {

    class IFrameNode {
    public:
        IFrameNode() {};
        IFrameNode(IFrameNode&) = delete;
        IFrameNode(IFrameNode&&) = delete;
        IFrameNode& operator=(IFrameNode&) = delete;
        IFrameNode& operator=(IFrameNode&&) = delete;

        virtual void Add(IFrameNode* child) {
            childs.push_back(child);
        }
        virtual void Erase(IFrameNode* child) {
            childs.erase(std::find(childs.begin(), childs.end(), child));
        }
        virtual void ClearChilds() {

        }
        virtual const std::list<IFrameNode*>& GetChilds() {
            return childs;
        }
        virtual IFrameNode* GetParent() {
            return parent;
        }

    private:
        IFrameNode* parent;
        std::list<IFrameNode*> childs;
    };

}