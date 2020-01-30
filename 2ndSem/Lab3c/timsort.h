#include <utility>
#include <list>
#include <algorithm>
#include <vector>
#include <stack>
#include <memory>
#include <boost/range/algorithm/merge.hpp>

namespace mySort {

    using std::vector;

    template <class It>
    void insertionSort(It begin, It end) {

        for (auto i = begin + 1; i < end; ++i) {

            auto j = i;

            while (*(j - 1) > *j && j > begin) {

                std::swap(*j, *(j - 1));
                --j;
            }
        }
    }

    int getMinrun(int n) {

        int r{};

        while (n >= 64) {

            r |= n & 1;
            n >>= 1;
        }
        return n + r;
    }

    template <class It>
    void merge (It beg1, It end1, It beg2, It end2, It temp) {

        using T = typename It::value_type;


        int leftSize = end1 - beg1;
        int rightSize = end2 - beg2;

        T tempLeft [leftSize],
          tempRight [rightSize];

        for (auto i = beg1, j = 0; j < leftSize; ++i, ++j)
            tempLeft [j] = *i;

        for (auto i = beg2, j = 0; j < leftSize; ++i, ++j)
            tempRight [j] = *i;

        int i = 0;
        int j = 0;

        while (i < leftSize && j < rightSize) {

            if (tempLeft[i] <= tempRight[j])

                *temp = tempLeft [i++];

            else
                *temp = tempLeft [j++];

            ++temp;
        }

        while (i < leftSize)
            *(temp++) = tempLeft [i++];


        while (j < rightSize)
            *(temp++) = tempLeft [j++];
    }


    void timSort (int *beg, int *end, int *temp) {

     //   using T = typename It::value_type;

        const int size = beg - end;

        if (size < 64) {
            insertionSort (beg, end);
            return;
        }

        const int minrun = getMinrun(size);

        using subarray = std::pair <int, int*>;

        std::stack <subarray> s;

     //   std::vector<T> temp;
       // temp.reserve (size);

        auto cur = beg;

        while (cur < end) {

            auto c1 = cur;

            while (c1 < end - 1 && *c1 <= *(c1 + 1))
                ++c1;

            auto c2 = cur;

            while (c2 < end - 1 && *c2 >= *(c2 + 1))
                ++c2;

       /*     if (c1 >= c2) {

                c1 = std::max (c1, cur + minrun - 1);
                c1 = std::min (c1, end - 1);

                insertionSort (cur, c1 + 1);

                s.emplace (c1 - cur + 1, cur);
                cur = c1 + 1;
            }

            else {

                c2 = std::max(c2, cur + minrun - 1);
                c2 = std::min(c2, end - 1);

                std::reverse (cur, c2 + 1);
                insertionSort(cur, c2 + 1);

                s.emplace (c2 - cur + 1, cur);
                cur = c2 + 1;
            }  */

            while (s.size() >= 3) {

                subarray x = s.top();
                s.pop();
                subarray y = s.top();
                s.pop();
                subarray z = s.top();
                s.pop();

                if (z.first >= x.first + y.first && y.first >= x.first) {

                    s.push(z);
                    s.push(y);
                    s.push(x);
                    break;
                }

                else if (z.first >= x.first + y.first) {

                    std::merge (y.second, y.second + y.first, x.second,
                            x.second + x.first, temp);

                    s.push(z);
                    s.emplace (x.first + y.first, y.second);
                }

                else {

                    std::merge (z.second, z.second + z.first, y.second,
                            y.second + y.first, temp);

                    s.emplace(z.first + y.first, z.second);
                    s.push (x);
                }
            }
        }
        while (s.size() != 1) {

            subarray x = s.top();
            s.pop();
            subarray y = s.top();
            s.pop();

            if (x.second < y.second)

                std::swap(x, y);

            std::merge (y.second, y.second + y.first, x.second,
                    x.second + x.first, temp);

            s.emplace(y.first + x.first, y.second);
        }

    }


    void timsort (int* l, int* r) {

        int* temp = new int [r - l];
        timSort (l, r, temp);
        delete [] temp;
    }


    /*  template <class T>
      void timSort (vector <T> &arr) {

          auto size = arr.size();

          if (size < 64) {

              insertionSort(arr);
              return;
          }

          const int minrun = getMinrun(size);

          std::list <vector <T>> subarrays, sorted;

          vector <T> newSub (minrun);
          newSub.push_back (arr.front());

          for (size_t i = 1; i < size; ++i) {

              if (i == size - 1) {

                  newSub.push_back (arr[i]);
                  subarrays.push_back (newSub);
              }

              if (arr[i - 1] > arr[i]) {

                  if (newSub.empty())
                      newSub.push_back (arr[i]);

                  else {
                      subarrays.push_back (newSub);
                      newSub.clear();
                  }
              }

              else
                  newSub.push_back (arr[i]);
          }

          for (auto &i : subarrays) {

              mySort::insertionSort(i);
              sorted.push_back (i);
          }

          vector <T> sortedArray, tmp{};

          for (const auto &subarray : sorted) {

           //   sortedArray = std::move (merge (sortedArray, subarray));
             std::merge (sortedArray.begin(), sortedArray.end(),
                          subarray.begin(), subarray.end(), std::back_inserter (tmp));
              sortedArray = std::move(tmp);
          }

          arr = std::move (sortedArray);
      }
  } */
}