#pragma once

#include <cstdint>

#include "array.h"
#include "bbox.h"
#include "vector3.h"

typedef uint16_t NodeIndex;
typedef uint32_t NodeDataReference;
typedef Vector3 NodeCenter;
typedef Bbox NodeBound;

static const NodeIndex INVALID_NODE = NodeIndex(~0); 
static const NodeIndex ROOT_NODE = NodeIndex(0); 
static const NodeIndex NUM_CHILDREN = 8;

static const NodeDataReference INVALID_DATAREFERENCE = NodeDataReference(~0);

struct Node {        
    NodeIndex child[NUM_CHILDREN]; // End of the list of children is flagged by an INVALID_NODE value 
};

struct OctreeConfiguration { 
    /**
     * Maximum depth of the tree. All data is referenced from maxDepth nodes
     */
    uint32_t maxDepth_;
    NodeCenter worldCenter_;
    float worldSize_;
    NodeIndex numDataEntries_; 
};

struct DataSpan {        
    uint16_t first_;
    uint16_t last_; // Inclusive 
};


struct Octree {
    OctreeConfiguration configuration;

    /**
     * Bounding boxes of all nodes (indexable by NodeIndex).
     */
    Array<NodeBound> nodeBounds;

    /**
     * Center of bounding boxes for all nodes (indexable by NodeIndex).
     */
    Array<NodeCenter> nodeCenter;

    /**
     * The array of actual nodes. Each node contains indices to it's eight children (indexable by NodeIndex).
     */
    Array<Node> nodeChildren;

    /**
     * Index into the array of data references for each node (indexable by NodeIndex). 
     * If a node contains no data, this is set to INVALID_DATAREFERENCE. 
     * Nodes of MAX_DEPTH must have a data reference. 
     * Nodes not of MAX_DEPTH must NOT have a data reference
     */
    Array<NodeDataReference> nodeDataReference;

    /**
     * An array of parent indices for each node (indexable by NodeIndex). 
     * This allows moving up the tree from child node to parent node.
     */
    Array<NodeIndex> nodeParents;

    /**
     * This array of DataSpan defines, for each NodeDataReference, the first index and the last index of the objects in the Content array which make up the contents of this node. 
     * (indexable by values stored in nodeD ataReferences)
     */
    Array<DataSpan> nodeContentSpans;

    /**
     * Array of "handles" to actual scene content (indexable by values stored in nodeContentSpans). 
     * The content for each node is contiguous, to allow the DataSpans to work. 
     * The way the reference is interpreted depends on the underlying subsystem, but typically it will be an index into an internal array of actual scene objects 
     * (e.g. terrain blocks or static scene objects).
     */
    Array<NodeDataReference> nodeContents;
};
