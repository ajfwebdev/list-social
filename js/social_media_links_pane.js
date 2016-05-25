/**
 * @file
 * JavaScript for the social media directory search functionality.
 *
 * @see social_media_links/plugins/content_types/social_media_links_pane.inc
 */

!(function ($) {

  Drupal.behaviors.social_media_links_pane_js = {
    attach: function (context, settings) {
      var options = {
        valueNames: ['lisearch-category', 'lisearch-link-span']
      };

      var socialMediaList = new List('lisearch-social-media-list', options);
    }
  }

})(jQuery);
