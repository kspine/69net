#ifndef __BOXNODE_H__
#define __BOXNODE_H__

namespace xxx
{
    struct BoxNode : public Node
    {
        BoxNode();
        void Draw( int durationTicks ) override;
        static BoxNode* Create() { return new BoxNode(); }
    };

}

#endif
