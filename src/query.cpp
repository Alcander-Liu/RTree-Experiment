#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include "RTree.h"

#define NUMDIMS	9

struct Rect
{
  Rect(){}
  Rect(int NUMDIYS)
  {
    int *min = new int[NUMDIYS];
    int *max = new int[NUMDIYS];
  }

  Rect(int *a_min, int *a_max, int NUMDIYS)
  {
    int *min = new int[NUMDIYS];
    int *max = new int[NUMDIYS];

    for(int i = 0; i < NUMDIYS; i++)
    {
      min[i] = a_min[i];
      max[i] = a_max[i];
    }
  }
};

bool MySearchCallback(int id, std::vector<int> *ids) 
{
  printf("Hit Image %d\n", id);
  ids->push_back(id);
  return true; // keep going
}

int main()
{
  std::string queryFile, featureFile;
  std::cout << "query file: ";
  std::cin >> queryFile;
  std::cout << "feature file: ";
  std::cin >> featureFile;

  std::ifstream query(queryFile);
  std::ifstream feature(featureFile);
  std::ifstream imageList("imagelist.txt");

  std::string * imageNames = new std::string[6000];
  std::string imageName;
  std::map<std::string, int> nameToIndex;
  for(int i = 0; imageList.good(); i++)
  {
    getline(imageList, imageName);
    imageNames[i] = imageName;
    nameToIndex.emplace(imageNames[i], i);
  }

  int **features = new int*[6000];
  for(int i = 0; i < 6000; i++)
    features[i] = new int[NUMDIMS];
  RTree<int, int, NUMDIMS, float> tree;
  for(int j = 0; feature.good(); j++)
  {
    for(int i = 0; i < NUMDIMS; i++)
      feature >> features[j][i];
    tree.Insert(features[j], features[j], j);
  }
  
  std::string queryName;
  int queryIndex;
  std::vector<int> ids;
  while(query.good())
  {
    getline(query, queryName);
    queryIndex = nameToIndex.at(queryName);
    tree.Search(features[queryIndex], features[queryIndex], MySearchCallback, &ids);
  }
  
  std::cout << "Search results: " << std::endl;
  for(int i = 0; i < ids.size(); i++)
    std::cout << imageNames[ids[i]] << std::endl;

  return 0;
}