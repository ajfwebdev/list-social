<?php
/**
 * @file
 * social_media_links.fieldable_panels_pane_type.inc
 */

/**
 * Implements hook_default_fieldable_panels_pane_type().
 */
function social_media_links_default_fieldable_panels_pane_type() {
  $export = array();

  $fieldable_panels_pane_type = new stdClass();
  $fieldable_panels_pane_type->disabled = FALSE; /* Edit this to true to make a default fieldable_panels_pane_type disabled initially */
  $fieldable_panels_pane_type->api_version = 1;
  $fieldable_panels_pane_type->name = 'social_media_link';
  $fieldable_panels_pane_type->title = 'Social Media Link';
  $fieldable_panels_pane_type->description = 'Social media link fields for each link that appears on the Social Media page.';
  $export['social_media_link'] = $fieldable_panels_pane_type;

  return $export;
}
