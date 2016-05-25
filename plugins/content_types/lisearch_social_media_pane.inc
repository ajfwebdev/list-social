<?php
/**
 * @file
 * A custom content pane to use to render a social media link directory.
 */

/**
 * Plugin array - used to describe the plugin.
 *
 * This is a Ctools content type plugin (a panels pane).
 *
 * 'title': This is the title of the plugin. It'll be used in the Panels
 *   administration area.
 * 'description': This is used as the description of the plugin, it's only
 *   used in the Panels administration area.
 * 'single': Content types have a concept called subtype.
 *   For basic content types leave this as TRUE.
 * 'content_types': This is the machine name of the plugin.
 * 'render callback': This is a callback to a function which will be used to
 *   render the content type.
 * 'required context': This tells Ctools which context is required for this
 *   content type. By using ctools_context_required(t('Node'), 'node'), this
 *   content type will only be available for node entities.
 * 'edit form': This is a callback for the edit form. Please note, this edit
 *   form must be implemented if you define a 'required context' key.
 * 'category': This allows you to add a content type into a Panels category.
 */

$plugin = array(
  'single' => TRUE,
  'content_types' => array('lisearch_social_media_pane'),
  'title' => t('Social Media Links Custom Pane'),
  'description' => t('A searchable directory of social media links.'),
  'category' => t('Custom'),
  'render callback' => 'lisearch_social_media_pane_render',
  'admin info' => 'lisearch_social_media_pane_admin_info',
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'defaults' => array(
    'text' => '',
  ),
  'all contexts' => TRUE,
);


/**
 * Render callback function.
 */
function lisearch_social_media_pane_render($subtype, $conf, $args, $context) {
  // Get the data for the social media list directory.
  $list_data = lisearch_get_list_data();
  // Create a block to display the list.
  $block = new stdClass();
  $block->content = theme('lisearch_build_social_media_list', array('list_data' => $list_data));

  return $block;
}

/**
 * Builds markup for rendering the list directory.
 *
 * @param array $variables
 *   An associative array containing:
 *   - associative arrays for each data set needed to build the various
 *     sections of the list.
 *
 * @return string
 *   The markup for the list.
 *
 * @ingroup themeable
 */
function theme_lisearch_build_social_media_list(array $variables) {
  $list_data = $variables['list_data'];
}

/**
 * Gets the list items from the database.
 *
 * @return array
 *   - an associative arrays containing the list items.
 */
function lisearch_get_list_data() {

  $query = 'SELECT
    fpp.fpid AS fpp_id,
    fpp.bundle AS fpp_bundle,
    fpp.title AS fpp_title,
    taxterm.name AS category_name,
    flinktxt.field_social_link_text_value AS link_text,
    flinkurl.field_social_link_url_value AS link_url
    FROM 
    {fieldable_panels_panes} fpp
    INNER JOIN
    {field_revision_field_related_department} freldept
    ON freldept.entity_id = fpp.fpid
    INNER JOIN
    {taxonomy_term_data} taxterm
    ON taxterm.tid = freldept.field_related_department_tid
    LEFT OUTER JOIN
    {field_data_field_social_link_text} flinktxt
    ON flinktxt.entity_id = fpp.fpid
    LEFT OUTER JOIN
    {field_revision_field_social_link_url} flinkurl
    ON flinkurl.entity_id = fpp.fpid
    WHERE fpp.bundle = :bundle
    ORDER BY category_name';

  $result = db_query($query, array(':bundle' => 'social_media_link'));
  $list_data = array();
  foreach ($result as $record) {
    if (!empty($record->category_name)) {
      $category = check_plain($record->category_name);
      $list_data[$category]['link_text'] = check_plain($record->link_text);
      $list_data[$category]['link_url'] = check_url($record->link_url);
    }
  }
  return $list_data;
}
