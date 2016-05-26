/**
 * @file
 * JavaScript for the social media directory search functionality.
 *
 * Source found here: https://kilianvalkhof.com/2010/javascript/how-to-build-a-fast-simple-list-filter-with-jquery/
 *
 * @see social_media_links/plugins/content_types/social_media_links_pane.inc
 */

!(function ($) {

  Drupal.behaviors.social_media_links_pane_js = {
    attach: function (context, settings) {

      var $outerWrapperDiv = $('.lisearch-outer-wrapper div', context);
      var $deptSearchBox = $('input.lisearch-dept-search-box', context);
      var $linkSearchBox = $('input.lisearch-link-search-box', context);

      listFilter();

      function listFilter() {

        $linkSearchBox.change(function () {

          // Get the value of the search input.
          var filter = $(this).val();
          $('ul', $outerWrapperDiv).each(function () {

            if (filter) {
              // Simple show/hide for list link items.
              $(this).find("a:not(:Contains(" + filter + "))").parent().slideUp();
              $(this).find("a:Contains(" + filter + ")").parent().slideDown();
            }
            else {
              $(this).find("li").slideDown();
            }

          });

        }).keyup(function () {
          // Trigger the above change after every letter.
          $(this).change();
        });

        $deptSearchBox.change(function () {

          // Get the value of the search input.
          var filter = $(this).val();
          $('.lisearch-dept-wrapper', context).each(function () {

            if (filter) {
              // Simple show/hide for department level.
              $(this).find("h3:not(:Contains(" + filter + "))").parent().slideUp();
              $(this).find("h3:Contains(" + filter + ")").parent().slideDown();
            }
            else {
              $(this).find("div").slideDown();
            }

          });

        }).keyup(function () {
          // Trigger the above change after every letter.
          $(this).change();
        });

      }
    }
  }

  /**
   * A case-insensitive version of the "contains" method.
   *
   * Source found here: https://kilianvalkhof.com/2010/javascript/how-to-build-a-fast-simple-list-filter-with-jquery/
   */
  jQuery.expr[':'].Contains = function(a,i,m) {
    return (a.textContent || a.innerText || "").toUpperCase().indexOf(m[3].toUpperCase()) >= 0;
  };

})(jQuery);
