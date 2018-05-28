#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include "RTree.h"

#define NUMDIMS	8

bool MySearchCallback(int id, std::vector<int> *ids) 
{
  ids->push_back(id);
  return true; // keep going
}

int main()
{
  std::cout << "Dimension: " << NUMDIMS << std::endl;
  std::string queryFile, featureFile;
  int range, dataAmount;
  std::cout << "query file: ";
  std::cin >> queryFile;
  std::cout << "feature file: ";
  std::cin >> featureFile;
  std::cout << "data amount: ";
  std::cin >> dataAmount;
  std::cout << "Range: "; // acceptable similarity range
  std::cin >> range;
  
  std::ifstream query(queryFile);
  std::ifstream feature(featureFile);
  std::ifstream imageList("imagelist.txt");

  // build two way index list of image names
  std::string * imageNames = new std::string[dataAmount];
  std::string imageName;
  std::map<std::string, int> nameToIndex;
  for(int i = 0; imageList.good(); i++)
  {
    getline(imageList, imageName);
    imageNames[i] = imageName;
    nameToIndex.emplace(imageNames[i], i);
  }

  // build R tree
  int **features = new int*[dataAmount];
  RTree<int, int, NUMDIMS, float> tree;
  for(int j = 0; j < dataAmount; j++)
  {
    features[j] = new int[NUMDIMS];
    for(int i = 0; i < NUMDIMS; i++)
      feature >> features[j][i];
    tree.Insert(features[j], features[j], j);
  }

  std::string queryName;
  std::vector<int> ids; //store search results
  int queryIndex, touchCount;
  int *queryRectMin = new int[NUMDIMS];
  int *queryRectMax = new int[NUMDIMS];

  while(query.good())
  {
    getline(query, queryName);
    queryIndex = nameToIndex.at(queryName);
    for(int i = 0; i < NUMDIMS; i++)
    {
      queryRectMax[i] = features[queryIndex][i] + range;
      queryRectMin[i] = features[queryIndex][i] - range;
    }
    touchCount = tree.Search(queryRectMin, queryRectMax, MySearchCallback, &ids);
    std::cout << queryName <<"  search results: " << std::endl;
    std::cout << "  Node touched times: " << touchCount << std::endl;
    for(int i = 0; i < ids.size(); i++)
      std::cout << "  " << imageNames[ids[i]] << std::endl;
    ids.clear();
  }
  
  

  return 0;
}