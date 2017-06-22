<?php
/**
 * @file
 * Adminstration settings for the Islandora custom_thumbnail module.
 */

/**
 * Adminstration form for the Islandora custom_thumbnail module.
 */
function islandora_custom_thumbnail_admin_settings(array $form, array &$form_state) {
  $form['islandora_custom_thumbnail_suppress_thumbnail_regeneration'] = array(
    '#type' => 'checkbox',
    '#title' => t('Suppress the regeneration of the TN datastream as a derivative.'),
    '#description' => t("This will stop the TN datastream being regenerated as a derivative."),
    '#default_value' => variable_get('islandora_custom_thumbnail_suppress_thumbnail_regeneration', TRUE),
  );
  return system_settings_form($form);
}
