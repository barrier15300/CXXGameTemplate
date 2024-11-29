#pragma once
#include "../Helper/DXHandle.h"

struct GraphData : public DXHandle<DXHandleType::Graph> {

	int InitImpl() {
		DeleteGraph(m_handle);
	}




};
