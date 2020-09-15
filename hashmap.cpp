template <typename T, typename V>
using hash_table = gp_hash_table<
  T,
  V,
  my_hash,
  equal_to<T>,
  direct_mask_range_hashing<>,
  linear_probe_fn<>,
  hash_standard_resize_policy<
    hash_exponential_size_policy<>,
    hash_load_check_resize_trigger<>,
    true
  >
>;
