#include "building.h"
using namespace std;
building::building()
{
    name="";
    is_ynical_bool=false;
    id_ynical_string="";
    Standart_time_building="";
    metter="";
    price="";
    ID="";
    //neded_material.clear();

    time_plan.clear();
    time_pair.date_start="";
    time_pair.date_fin="";
    metter_pair.metter_fin="";
    metter_pair.metter_start="";
    price_pair.price_fin="";
    price_pair.price_start="";
}

building::~building()
{

}
void make_and_save_time_plan_for_building()
{

}
