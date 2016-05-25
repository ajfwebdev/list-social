<?php
/**
 * @file
 * social_media_links.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function social_media_links_taxonomy_default_vocabularies() {
  return array(
    'social_media_hierarchy' => array(
      'name' => 'Social Media Hierarchy',
      'machine_name' => 'social_media_hierarchy',
      'description' => 'Terms to organize social media links',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
  );
}
