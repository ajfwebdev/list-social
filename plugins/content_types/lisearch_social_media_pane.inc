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

  // Create a block to display the list.
  $block = new stdClass();
  $block->content = theme('lisearch_build_social_media_list',
    array(

    ));

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

}
