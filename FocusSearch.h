#pragma once
#include "UllmansAlgorithm.h"

class FocusSearch : public UllmansAlgorithm {
    using UllmansAlgorithm::UllmansAlgorithm;
public:
    int findIsomorphisms() override;
private:
    void initialize() override;
    int refine() override;
    
};