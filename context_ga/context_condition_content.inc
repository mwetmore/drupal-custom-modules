<?php
/**
 * Expose GA Content as a context condition.
 */
class context_condition_content extends context_condition {
  /**
   * Omit condition values. We will provide a custom input form for our conditions.
   */
  function condition_values() {
    return array();
  }

  /**
   * Condition form.
   */
  function condition_form($context) {
    $form = parent::condition_form($context);
    unset($form['#options']);

    $form['#type'] = 'textarea';
    $form['#default_value'] = implode("\n", $this->fetch_from_context($context, 'values'));
    return $form;
  }

  /**
   * Condition form submit handler.
   */
  function condition_form_submit($values) {
    $parsed = array();
    $items = explode("\n", $values);
    if (!empty($items)) {
      foreach ($items as $v) {
        $v = trim($v);
        if (!empty($v)) {
          $parsed[$v] = $v;
        }
      }
    }
    return $parsed;
  }

  /**
   * Execute.
   */
  function execute() {
    if ($this->condition_used()) {
      // Include both the keywords alias and normal keywords for matching.
      $tokentext = "[ga_tokenizer:ga-content]";
      $ga_content = token_replace($tokentext);
      $default = TRUE;
      foreach ($this->get_contexts() as $context) {
        $content = $this->fetch_from_context($context, 'values');
        if ($this->match($ga_content, $content, FALSE)) {
          $default = FALSE;
          $this->condition_met($context);
        }
      }

      if ($default) {
        foreach ($this->get_contexts() as $context) {
          $content = $this->fetch_from_context($context, 'values');
          if ($this->match($ga_content, $content, TRUE)) {
            $this->condition_met($context);
          }
        }
      }
    }
  } 

  

  /**
   * Match the subject against a set of regex patterns.
   * Similar to drupal_match_keywords() but also handles negation through the use
   * of the ~ character.
   *
   * @param mixed $subject
   *   The subject string or an array of strings to be matched.
   * @param array $patterns
   *   An array of patterns. Any patterns that begin with ~ are considered
   *   negative or excluded conditions.
   * @param boolean $keywords
   *   Whether the given subject should be matched as a Drupal keywords. If TRUE,
   *   '<front>' will be replaced with the site frontpage when matching against
   *   $patterns.
   *   '<default>' will activate if no contexts activate when $patterns = FALSE
   *
   */
  protected function match($subject, $patterns, $keywords = FALSE) {
    static $regexps;
    $match  = FALSE;
    $positives = $negatives = 0;
    $subject = !is_array($subject) ? array($subject) : $subject;
    foreach ($patterns as $pattern) {
      $pattern = strtolower($pattern);
      if (strpos($pattern, '~') === 0) {
        $negate = TRUE;
        $negatives++;
      }
      else {
        $negate = FALSE;
        $positives++;
      }
      $pattern = ltrim($pattern, '~');
      if (!isset($regexps[$pattern])) {
        $regexps[$pattern] = '/^('. preg_replace(array('/(\r\n?|\n)/', '/\\\\\*/'), array('|', '.*'), preg_quote($pattern, '/')) .')$/';
      }
      foreach ($subject as $value) {
        $value = strtolower($value);
        if (preg_match($regexps[$pattern], $value)) {
          if ($negate) {
            return FALSE;
          }
          $match = TRUE;
        }
      }
      if ($keywords && $pattern == '<default>') {
          $match = TRUE;
      }
    }
    // If there are **only** negative conditions and we've gotten this far none
    // we actually have a match.
    if ($positives === 0 && $negatives) {
      return TRUE;
    }
    return $match;
  }
}

