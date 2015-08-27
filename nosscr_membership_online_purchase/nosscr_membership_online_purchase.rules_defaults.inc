<?php
/**
 * @file
 * nosscr_membership_online_purchase.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function nosscr_membership_online_purchase_default_rules_configuration() {
  $items = array();
  $items['commerce_shipping_service_flat_rate_10_shipping'] = entity_import('rules_config', '{ "commerce_shipping_service_flat_rate_10_shipping" : {
      "LABEL" : "Rate Flat Rate - $10 Shipping",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "USES VARIABLES" : { "commerce_order" : { "label" : "Order", "type" : "commerce_order" } },
      "DO" : [ { "commerce_shipping_service_rate_order" : [] } ]
    }
  }');
  $items['rules_add_membership_product_to_cart_after_filling_out_membershi'] = entity_import('rules_config', '{ "rules_add_membership_product_to_cart_after_filling_out_membershi" : {
      "LABEL" : "Regular Membership: Add membership product to cart after filling out membership form",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "php", "rules", "commerce_cart", "webform_rules" ],
      "ON" : { "webform_rules_submit" : [] },
      "IF" : [
        { "php_eval" : { "code" : "if($data[\\u0027components\\u0027][\\u0027membership_type\\u0027][\\u0027value\\u0027][0] == \\u0027regular\\u0027) { return TRUE; } else { return FALSE; }" } }
      ],
      "DO" : [
        { "commerce_cart_product_add_by_sku" : {
            "USING" : {
              "user" : [ "user" ],
              "sku" : "MEMBER-REG",
              "quantity" : "1",
              "combine" : 1
            },
            "PROVIDE" : { "product_add_line_item" : { "product_add_line_item" : "Added product line item" } }
          }
        },
        { "drupal_message" : { "message" : "Thank you for your submission. You may now pay for your membership here." } },
        { "redirect" : { "url" : "\\/checkout" } }
      ]
    }
  }');
  $items['rules_hide_shipping_if_only_membership'] = entity_import('rules_config', '{ "rules_hide_shipping_if_only_membership" : {
      "LABEL" : "Hide Shipping if Only Membership",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "commerce_order", "commerce_rules_extra" ],
      "ON" : { "commerce_rules_extra_process_checkout_pane" : [] },
      "IF" : [
        { "NOT commerce_order_contains_product_type" : {
            "commerce_order" : [ "commerce_order" ],
            "product_type" : { "value" : { "product" : "product" } },
            "operator" : "\\u003E=",
            "value" : "1"
          }
        }
      ],
      "DO" : [
        { "commerce_rules_extra_change_pane" : {
            "pane_id" : "customer_profile_shipping",
            "page_id" : "\\u003Csame\\u003E",
            "enabled" : 0
          }
        },
        { "commerce_rules_extra_change_pane" : {
            "pane_id" : "commerce_shipping",
            "page_id" : "\\u003Csame\\u003E",
            "enabled" : 0
          }
        }
      ]
    }
  }');
  $items['rules_sustaning_membership_add_membership_product_to_cart_after_'] = entity_import('rules_config', '{ "rules_sustaning_membership_add_membership_product_to_cart_after_" : {
      "LABEL" : "Sustaning Membership: Add membership product to cart after filling out membership form",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "php", "rules", "commerce_cart", "webform_rules" ],
      "ON" : { "webform_rules_submit" : [] },
      "IF" : [
        { "php_eval" : { "code" : "if($data[\\u0027components\\u0027][\\u0027membership_type\\u0027][\\u0027value\\u0027][0] == \\u0027sustaining\\u0027) { return TRUE; } else { return FALSE; }" } }
      ],
      "DO" : [
        { "commerce_cart_product_add_by_sku" : {
            "USING" : {
              "user" : [ "user" ],
              "sku" : "MEMBER-SUST",
              "quantity" : "1",
              "combine" : 1
            },
            "PROVIDE" : { "product_add_line_item" : { "product_add_line_item" : "Added product line item" } }
          }
        },
        { "drupal_message" : { "message" : "Thank you for your submission. You may now pay for your membership here." } },
        { "redirect" : { "url" : "\\/checkout" } }
      ]
    }
  }');
  return $items;
}
