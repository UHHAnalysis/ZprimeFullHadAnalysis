#ifndef HEPTopTaggerReweight_H
#define HEPTopTaggerReweight_H
#include<vector>
#include<string>

using namespace std;

/**
 *  @module to apply data-MC scale factors for b tagging
 *
 *
 */
class HEPTopTaggerReweight {
public:
    /**
     * constructor
     *
     */
    HEPTopTaggerReweight() {};
    ///Default destructor
    ~HEPTopTaggerReweight() {};

    ///return the weighted correction factor
    double GetScaleWeight(std::vector<int> Indices, string type="");

private:
                 
};

#endif
