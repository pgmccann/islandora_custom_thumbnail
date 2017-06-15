<?php

/**
 * @file
 * Upload thumbnail image file.
 */

/**
 * Upload thumbnail image form.
 *
 * @param array $form
 *   The Drupal form.
 * @param array $form_state
 *   The Drupal form state.
 *
 * @return array
 *   A Drupal form definition.
 */
function islandora_custom_thumbnail_file_form(array $form, array &$form_state) {
  return array(
    'thumbnail' => array(
      '#type' => 'managed_file',
      '#title' => t('Thumbnail Image'),
      '#description' => t('A JPG image file to be used as a thumbnail for the object. Click "Next" to skip this step and have the thumbnail generated as a derivative.'),
      '#upload_validators' => array(
        'file_validate_extensions' => array('jpg', 'jpeg', 'JPG', 'JPEG'),
      ),
    ),
  );
}

/**
 * Handle the uploaded thumbnail image.
 *
 * Only populates the MODS datastream if a file was uploaded.
 *
 * @param array $form
 *   The Drupal form.
 * @param array $form_state
 *   The Drupal form state.
 */
function islandora_custom_thumbnail_file_form_submit(array &$form, array &$form_state) {
  module_load_include('inc', 'islandora_custom_thumbnail', 'includes/utilities');
  $file = file_load($form_state['values']['thumbnail']);
  if ($file) {
    $tn_step_storage = &islandora_ingest_form_get_step_storage($form_state, 'islandora_custom_thumbnail_upload');
    $object = islandora_ingest_form_get_object($form_state);
    $dsid = 'TN';
    $datastream = isset($object[$dsid]) ? $object[$dsid] : $object->constructDatastream($dsid);
    $datastream->label = $dsid;
    $datastream->mimeType = 'image/jpeg';
    $file_path = file_save($file);
    $datastream->setContentFromFile($file_path->uri);
    // Ingest the datastream if it isn't yet.
    if (!isset($object[$dsid])) {
      $object->ingestDatastream($datastream);
    }
    // To ensure the file is only used once, delete it.
    file_delete($file);
    unset($form_state['values']['file']);
  }
}
