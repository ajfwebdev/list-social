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
  'content_types' => array('social_media_links_pane'),
  'title' => t('Social Media Links Custom Pane'),
  'description' => t('A searchable directory of social media links.'),
  'category' => t('Custom blocks'),
  'render callback' => 'social_media_links_pane_render',
  'admin info' => 'social_media_links_pane_admin_info',
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'defaults' => array(
    'text' => '',
  ),
  'all contexts' => TRUE,
);


/**
 * Render callback function.
 */
function social_media_links_pane_render($subtype, $conf, $args, $context) {
  // Get the data for the social media list directory.
  $list_data = social_media_links_pane_list_data();
  // Create a block to display the list.
  $block = new stdClass();
  $block->content = social_media_links_pane_build_list($list_data);

  return $block;
}

/**
 * Builds markup for rendering the list directory.
 *
 * @param array $list_data
 *   An associative array containing:
 *   - data needed to build the various sections of the list.
 *
 * @return string
 *   The markup for the list.
 */
function social_media_links_pane_build_list(array $list_data) {
  $output = '';
  $output .= '<div id="lisearch-social-media-list" class="social-media-links">';
  $output .= '<input class="search" placeholder="Search" />';

  // The "list" class is required on the ul element.
  $output .= '<ul class="list">';
  foreach ($list_data as $category_data) {
    $output .= '<li class="lisearch-cat-li"><h3 class="lisearch-category">' . $category_data['category_name'] . '</h3></li>';
    foreach ($category_data as $key => $value) {
      if ($key !== 'category_name') {
        if (isset($value['link_url']) && isset($value['link_text'])) {
          $output .= '<li class="lisearch-link-li">';
          $output .= '<a class="lisearch-link" href="' . $value['link_url'] . '" target="_blank"><span class="lisearch-link-span">';
          $output .= $value['link_text'];
          $output .= '</span></a>';
          $output .= '</li>';
        }
      }
    }
  }
  $output .= '</ul>';
  $output .= '</div>';
  return $output;
}

/**
 * Gets the list items from the database.
 *
 * @return array
 *   - an associative arrays containing the list items.
 */
function social_media_links_pane_list_data() {

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
  $category_hold = '';
  $child_array = array();
  foreach ($result as $record) {
    if (!empty($record->category_name)) {
      $category_in = check_plain($record->category_name);
      if ($category_in != $category_hold) {
        if (!empty($child_array)) {
          $list_data[] = $child_array;
          unset($child_array);
          $child_array = array();
        }
        $child_array['category_name'] = $category_in;
        $category_hold = $category_in;
      }
      $link_text = check_plain($record->link_text);
      $link_key = str_replace(' ', '_', strtolower($link_text));
      $child_array[$link_key] = array('link_text' => $link_text, 'link_url' => check_url($record->link_url));
    }
  }

  return $list_data;
}

/**
 * Admin info callback for panel pane.
 */
function social_media_links_pane_admin_info($subtype, $conf, $context) {
  // Set the title that shows on the admin Content page to the overridden title.
  $block = new stdClass();
  $block->title = t('Social Media Links');
  return $block;
}
