/*
 * Copyright © 2010 Codethink Limited
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2 of the licence or (at
 * your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * Authors: Ryan Lortie <desrt@desrt.ca>
 */

#if !defined (__GIO_GIO_H_INSIDE__) && !defined (GIO_COMPILATION)
#error "Only <gio/gio.h> can be included directly."
#endif

#ifndef __G_ACTION_GROUP_H__
#define __G_ACTION_GROUP_H__

#include <gio/giotypes.h>

G_BEGIN_DECLS


#define G_TYPE_ACTION_GROUP                                 (g_action_group_get_type ())
#define G_ACTION_GROUP(inst)                                (G_TYPE_CHECK_INSTANCE_CAST ((inst),                     \
                                                             G_TYPE_ACTION_GROUP, GActionGroup))
#define G_IS_ACTION_GROUP(inst)                             (G_TYPE_CHECK_INSTANCE_TYPE ((inst),                     \
                                                             G_TYPE_ACTION_GROUP))
#define G_ACTION_GROUP_GET_IFACE(inst)                      (G_TYPE_INSTANCE_GET_INTERFACE ((inst),                  \
                                                             G_TYPE_ACTION_GROUP, GActionGroupInterface))

typedef struct _GActionGroupInterface                       GActionGroupInterface;

/**
 * GActionGroupInterface:
 * @has_action: the virtual function pointer for g_action_group_has_action()
 * @list_actions: the virtual function pointer for g_action_group_list_actions()
 * @get_action_parameter_type: the virtual function pointer for g_action_group_get_action_parameter_type()
 * @get_action_state_type: the virtual function pointer for g_action_group_get_action_state_type()
 * @get_action_state_hint: the virtual function pointer for g_action_group_get_action_state_hint()
 * @get_action_enabled: the virtual function pointer for g_action_group_get_action_enabled()
 * @get_action_state: the virtual function pointer for g_action_group_get_action_state()
 * @set_action_state: the virtual function pointer for g_action_group_set_action_state()
 * @activate_action: the virtual function pointer for g_action_group_activate_action()
 * @action_added: the class closure for the #GActionGroup::action-added signal
 * @action_removed: the class closure for the #GActionGroup::action-removed signal
 * @action_enabled_changed: the class closure for the #GActionGroup::action-enabled-changed signal
 * @action_state_changed: the class closure for the #GActionGroup::action-enabled-changed signal
 *
 * The virtual function table for #GActionGroup.
 *
 * Since: 2.28
 */
struct _GActionGroupInterface
{
  GTypeInterface g_iface;

  /* virtual functions */
  gboolean              (* has_action)                 (GActionGroup  *action_group,
                                                        const gchar   *action_name);

  gchar **              (* list_actions)               (GActionGroup  *action_group);

  gboolean              (* get_action_enabled)         (GActionGroup  *action_group,
                                                        const gchar   *action_name);

  const GVariantType *  (* get_action_parameter_type)  (GActionGroup  *action_group,
                                                        const gchar   *action_name);

  const GVariantType *  (* get_action_state_type)      (GActionGroup  *action_group,
                                                        const gchar   *action_name);

  GVariant *            (* get_action_state_hint)      (GActionGroup  *action_group,
                                                        const gchar   *action_name);

  GVariant *            (* get_action_state)           (GActionGroup  *action_group,
                                                        const gchar   *action_name);

  void                  (* change_action_state)        (GActionGroup  *action_group,
                                                        const gchar   *action_name,
                                                        GVariant      *value);

  void                  (* activate_action)            (GActionGroup  *action_group,
                                                        const gchar   *action_name,
                                                        GVariant      *parameter);

  /* signals */
  void                  (* action_added)               (GActionGroup  *action_group,
                                                        const gchar   *action_name);
  void                  (* action_removed)             (GActionGroup  *action_group,
                                                        const gchar   *action_name);
  void                  (* action_enabled_changed)     (GActionGroup  *action_group,
                                                        const gchar   *action_name,
                                                        gboolean       enabled);
  void                  (* action_state_changed)       (GActionGroup   *action_group,
                                                        const gchar    *action_name,
                                                        GVariant       *state);
};

GType                   g_action_group_get_type                         (void) G_GNUC_CONST;

gboolean                g_action_group_has_action                       (GActionGroup *action_group,
                                                                         const gchar  *action_name);
gchar **                g_action_group_list_actions                     (GActionGroup *action_group);

const GVariantType *    g_action_group_get_action_parameter_type        (GActionGroup *action_group,
                                                                         const gchar  *action_name);
const GVariantType *    g_action_group_get_action_state_type            (GActionGroup *action_group,
                                                                         const gchar  *action_name);
GVariant *              g_action_group_get_action_state_hint            (GActionGroup *action_group,
                                                                         const gchar  *action_name);

gboolean                g_action_group_get_action_enabled               (GActionGroup *action_group,
                                                                         const gchar  *action_name);

GVariant *              g_action_group_get_action_state                 (GActionGroup *action_group,
                                                                         const gchar  *action_name);
void                    g_action_group_change_action_state              (GActionGroup *action_group,
                                                                         const gchar  *action_name,
                                                                         GVariant     *value);

void                    g_action_group_activate_action                  (GActionGroup *action_group,
                                                                         const gchar  *action_name,
                                                                         GVariant     *parameter);

/* signals */
void                    g_action_group_action_added                     (GActionGroup *action_group,
                                                                         const gchar  *action_name);
void                    g_action_group_action_removed                   (GActionGroup *action_group,
                                                                         const gchar  *action_name);
void                    g_action_group_action_enabled_changed           (GActionGroup *action_group,
                                                                         const gchar  *action_name,
                                                                         gboolean      enabled);

void                    g_action_group_action_state_changed             (GActionGroup *action_group,
                                                                         const gchar  *action_name,
                                                                         GVariant     *state);

G_END_DECLS

#endif /* __G_ACTION_GROUP_H__ */
