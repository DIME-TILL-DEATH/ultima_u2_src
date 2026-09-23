#ifndef __TUPLE_ACCESS_H__
#define __TUPLE_ACCESS_H__


#include <tuple>


namespace tuple_access
{


template <std::size_t...Is>
struct index_sequence
{};

template <std::size_t N, std::size_t...Is>
struct build : public build<N - 1, N - 1, Is...>
{};

template <std::size_t...Is>
struct build<0, Is...>
{
    using type = index_sequence<Is...>;
};

template <std::size_t N>
using make_index_sequence = typename build<N>::type;

template <typename T>
using remove_reference_t = typename std::remove_reference<T>::type;

namespace detail
{
  template <class Tuple, class F, std::size_t...Is>
  void tuple_switch(const std::size_t i, Tuple&& t, F&& f, index_sequence<Is...>)
    {
     [](...){}((i == Is && ((void)std::forward<F>(f)(std::get<Is>(std::forward<Tuple>(t))), false))...);
    }
} // namespace detail

template <class Tuple, class F>
void tuple_switch(const std::size_t i, Tuple&& t, F&& f) {
  static constexpr auto N =
    std::tuple_size<remove_reference_t<Tuple>>::value;

  detail::tuple_switch(i, std::forward<Tuple>(t), std::forward<F>(f),
                       make_index_sequence<N>{});
}

constexpr struct {
  template <typename T>
  void operator()(const T& t) const
  {
      //std::cout << t << '\n';
  }
} print{};

}

#endif /* __TUPLE_ACCESS_H__*/
