#include "S_Sample.h"

void S_Sample::Init() {
	m_Objects.push_back(std::make_unique<O_Sample>());
}

void S_Sample::End() {

}
