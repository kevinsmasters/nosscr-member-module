<?php
/**
 * @file
 * nosscr_membership_online_purchase.features.inc
 */

/**
 * Implements hook_commerce_product_default_types().
 */
function nosscr_membership_online_purchase_commerce_product_default_types() {
  $items = array(
    'membership' => array(
      'type' => 'membership',
      'name' => 'Membership',
      'description' => 'for First Time and Renewal memberships',
      'help' => '',
      'revision' => 1,
    ),
  );
  return $items;
}
