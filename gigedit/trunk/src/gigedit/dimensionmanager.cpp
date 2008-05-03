/*                                                         -*- c++ -*-
 * Copyright (C) 2006-2008 Andreas Persson
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with program; see the file COPYING. If not, write to the Free
 * Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA.
 */

#include "dimensionmanager.h"

#include <gtkmm/stock.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/dialog.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/table.h>

// returns a human readable name of the given dimension type
static Glib::ustring __dimTypeAsString(gig::dimension_t d) {
    char buf[32];
    switch (d) {
        case gig::dimension_none:
            return "None";
        case gig::dimension_samplechannel:
            return "Sample Channel";
        case gig::dimension_layer:
            return "Layer";
        case gig::dimension_velocity:
            return "Velocity";
        case gig::dimension_channelaftertouch:
            return "Aftertouch";
        case gig::dimension_releasetrigger:
            return "Release Trigger";
        case gig::dimension_keyboard:
            return "Keyswitching";
        case gig::dimension_roundrobin:
            return "Round Robin";
        case gig::dimension_random:
            return "Random Generator";
        case gig::dimension_smartmidi:
            return "Smart MIDI";
        case gig::dimension_roundrobinkeyboard:
            return "Keyboard Round Robin";
        case gig::dimension_modwheel:
            return "Modulation Wheel";
        case gig::dimension_breath:
            return "Breath Ctrl.";
        case gig::dimension_foot:
            return "Foot Ctrl.";
        case gig::dimension_portamentotime:
            return "Portamento Time Ctrl.";
        case gig::dimension_effect1:
            return "Effect Ctrl. 1";
        case gig::dimension_effect2:
            return "Effect Ctrl. 2";
        case gig::dimension_genpurpose1:
            return "General Purpose Ctrl. 1";
        case gig::dimension_genpurpose2:
            return "General Purpose Ctrl. 2";
        case gig::dimension_genpurpose3:
            return "General Purpose Ctrl. 3";
        case gig::dimension_genpurpose4:
            return "General Purpose Ctrl. 4";
        case gig::dimension_sustainpedal:
            return "Sustain Pedal";
        case gig::dimension_portamento:
            return "Portamento Ctrl.";
        case gig::dimension_sostenutopedal:
            return "Sostenuto Pedal";
        case gig::dimension_softpedal:
            return "Soft Pedal";
        case gig::dimension_genpurpose5:
            return "General Purpose Ctrl. 5";
        case gig::dimension_genpurpose6:
            return "General Purpose Ctrl. 6";
        case gig::dimension_genpurpose7:
            return "General Purpose Ctrl. 7";
        case gig::dimension_genpurpose8:
            return "General Purpose Ctrl. 8";
        case gig::dimension_effect1depth:
            return "Effect 1 Depth";
        case gig::dimension_effect2depth:
            return "Effect 2 Depth";
        case gig::dimension_effect3depth:
            return "Effect 3 Depth";
        case gig::dimension_effect4depth:
            return "Effect 4 Depth";
        case gig::dimension_effect5depth:
            return "Effect 5 Depth";
        default:
            sprintf(buf, "Unknown Type (0x%x) !!!", d);
            return buf;
    }
}

// returns a human readable description of the given dimension
static Glib::ustring __dimDescriptionAsString(gig::dimension_t d) {
    switch (d) {
        case gig::dimension_none:
            return "Dimension not in use";
        case gig::dimension_samplechannel:
            return "If used sample has more than one channel (thus is not mono)";
        case gig::dimension_layer:
            return "For layering of up to 8 instruments (and eventually crossfading of 2 or 4 layers";
        case gig::dimension_velocity:
            return "Key Velocity (this is the only dimension in gig2 where the ranges can exactly be defined)";
        case gig::dimension_channelaftertouch:
            return "Channel Key Pressure";
        case gig::dimension_releasetrigger:
            return "Special dimension for triggering samples on releasing a key";
        case gig::dimension_keyboard:
            return "Dimension for keyswitching (keyboard)";
        case gig::dimension_roundrobin:
            return "Different samples triggered each time a note is played, dimension regions selected in sequence";
        case gig::dimension_random:
            return "Different samples triggered each time a note is played, random order";
        case gig::dimension_smartmidi:
            return "For MIDI tools like legato and repetition mode";
        case gig::dimension_roundrobinkeyboard:
            return "Different samples triggered each time a note is played, any key advances the counter";
        case gig::dimension_modwheel:
            return "MIDI Controller 1";
        case gig::dimension_breath:
            return "MIDI Controller 2";
        case gig::dimension_foot:
            return "MIDI Controller 4";
        case gig::dimension_portamentotime:
            return "MIDI Controller 5";
        case gig::dimension_effect1:
            return "MIDI Controller 12";
        case gig::dimension_effect2:
            return "MIDI Controller 13";
        case gig::dimension_genpurpose1:
            return "Slider, MIDI Controller 16";
        case gig::dimension_genpurpose2:
            return "Slider, MIDI Controller 17";
        case gig::dimension_genpurpose3:
            return "Slider, MIDI Controller 18";
        case gig::dimension_genpurpose4:
            return "Slider, MIDI Controller 19";
        case gig::dimension_sustainpedal:
            return "MIDI Controller 64";
        case gig::dimension_portamento:
            return "MIDI Controller 65";
        case gig::dimension_sostenutopedal:
            return "MIDI Controller 66";
        case gig::dimension_softpedal:
            return "MIDI Controller 67";
        case gig::dimension_genpurpose5:
            return "Button, MIDI Controller 80";
        case gig::dimension_genpurpose6:
            return "Button, MIDI Controller 81";
        case gig::dimension_genpurpose7:
            return "Button, MIDI Controller 82";
        case gig::dimension_genpurpose8:
            return "Button, MIDI Controller 83";
        case gig::dimension_effect1depth:
            return "MIDI Controller 91";
        case gig::dimension_effect2depth:
            return "MIDI Controller 92";
        case gig::dimension_effect3depth:
            return "MIDI Controller 93";
        case gig::dimension_effect4depth:
            return "MIDI Controller 94";
        case gig::dimension_effect5depth:
            return "MIDI Controller 95";
        default:
            return "Please report this !!!";
    }
}

DimensionManager::DimensionManager() :
addButton(Gtk::Stock::ADD), removeButton(Gtk::Stock::REMOVE)
{
    set_title("Dimensions of selected Region");
    add(vbox);
    scrolledWindow.add(treeView);
    vbox.pack_start(scrolledWindow);
    scrolledWindow.show();
    vbox.pack_start(buttonBox, Gtk::PACK_SHRINK);
    buttonBox.set_layout(Gtk::BUTTONBOX_END);
    buttonBox.set_border_width(5);
    buttonBox.show();
    buttonBox.pack_start(addButton, Gtk::PACK_SHRINK);
    buttonBox.pack_start(removeButton, Gtk::PACK_SHRINK);
    addButton.show();
    removeButton.show();

    // setup the table
    refTableModel = Gtk::ListStore::create(tableModel);
    treeView.set_model(refTableModel);
    treeView.append_column("Dimension Type", tableModel.m_dim_type);
    treeView.append_column("Bits", tableModel.m_bits);
    treeView.append_column("Zones", tableModel.m_zones);
    treeView.append_column("Description", tableModel.m_description);
    treeView.show();

    addButton.signal_clicked().connect(
        sigc::mem_fun(*this, &DimensionManager::addDimension)
    );

    removeButton.signal_clicked().connect(
        sigc::mem_fun(*this, &DimensionManager::removeDimension)
    );

    show_all_children();
}

// update all GUI elements according to current gig::Region informations
void DimensionManager::refreshManager() {
    refTableModel->clear();
    if (region) {
        for (int i = 0; i < region->Dimensions; i++) {
            gig::dimension_def_t* dim = &region->pDimensionDefinitions[i];
            Gtk::TreeModel::Row row = *(refTableModel->append());
            row[tableModel.m_dim_type] = __dimTypeAsString(dim->dimension);
            row[tableModel.m_bits] = dim->bits;
            row[tableModel.m_zones] = dim->zones;
            row[tableModel.m_description] = __dimDescriptionAsString(dim->dimension);
            row[tableModel.m_definition] = dim;
        }
    }
    set_sensitive(region);
}

void DimensionManager::show(gig::Region* region) {
    this->region = region;
    refreshManager();
    Gtk::Window::show();
    deiconify();
}

void DimensionManager::set_region(gig::Region* region) {
    this->region = region;
    refreshManager();
}

void DimensionManager::addDimension() {
    try {
        Gtk::Dialog dialog("New Dimension", true /*modal*/);
        // add dimension type combo box to the dialog
        Glib::RefPtr<Gtk::ListStore> refComboModel = Gtk::ListStore::create(comboModel);
        for (int i = 0x01; i < 0xff; i++) {
            Glib::ustring sType =
                __dimTypeAsString(static_cast<gig::dimension_t>(i));
            if (sType.find("Unknown") != 0) {
                Gtk::TreeModel::Row row = *(refComboModel->append());
                row[comboModel.m_type_id]   = i;
                row[comboModel.m_type_name] = sType;
            }
        }
        Gtk::Table table(2, 2);
        Gtk::Label labelDimType("Dimension:", Gtk::ALIGN_LEFT);
        Gtk::ComboBox comboDimType;
        comboDimType.set_model(refComboModel);
        comboDimType.pack_start(comboModel.m_type_id);
        comboDimType.pack_start(comboModel.m_type_name);
        Gtk::Label labelZones("Zones:", Gtk::ALIGN_LEFT);
        table.attach(labelDimType, 0, 1, 0, 1);
        table.attach(comboDimType, 1, 2, 0, 1);
        table.attach(labelZones, 0, 1, 1, 2);
        dialog.get_vbox()->pack_start(table);

        // number of zones: use a combo box with fix values for gig
        // v2 and a spin button for v3
        Gtk::ComboBoxText comboZones;
        Gtk::SpinButton spinZones;
        bool version2 = false;
        if (region) {
            gig::File* file = (gig::File*)region->GetParent()->GetParent();
            version2 = file->pVersion && file->pVersion->major == 2;
        }
        if (version2) {
            for (int i = 1; i <= 5; i++) {
                char buf[3];
                sprintf(buf, "%d", 1 << i);
                comboZones.append_text(buf);
            }
            table.attach(comboZones, 1, 2, 1, 2);
        } else {
            spinZones.set_increments(1, 8);
            spinZones.set_numeric(true);
            spinZones.set_range(2, 128);
            spinZones.set_value(2);
            table.attach(spinZones, 1, 2, 1, 2);
        }

        dialog.add_button(Gtk::Stock::OK, 0);
        dialog.add_button(Gtk::Stock::CANCEL, 1);
        dialog.show_all_children();

        if (!dialog.run()) { // OK selected ...
            Gtk::TreeModel::iterator iterType = comboDimType.get_active();
            if (!iterType) return;
            Gtk::TreeModel::Row rowType = *iterType;
            if (!rowType) return;
            gig::dimension_def_t dim;
            int iTypeID = rowType[comboModel.m_type_id];
            dim.dimension = static_cast<gig::dimension_t>(iTypeID);

            if (version2) {
                if (comboZones.get_active_row_number() < 0) return;
                dim.bits = comboZones.get_active_row_number() + 1;
                dim.zones = 1 << dim.bits;
            } else {
                dim.zones = spinZones.get_value_as_int();
                // Find the number of bits required to hold the
                // specified amount of zones.
                int zoneBits = dim.zones - 1;
                for (dim.bits = 0; zoneBits > 1; dim.bits += 2, zoneBits >>= 2);
                dim.bits += zoneBits;
            }
            printf(
                "Adding dimension (type=0x%x, bits=%d, zones=%d)\n",
                dim.dimension, dim.bits, dim.zones
            );
            // notify everybody that we're going to update the region
            region_to_be_changed_signal.emit(region);
            // add the new dimension to the region
            // (implicitly creates new dimension regions)
            region->AddDimension(&dim);
            // let everybody know there was a change
            region_changed_signal.emit(region);
            // update all GUI elements
            refreshManager();
        }
    } catch (RIFF::Exception e) {
        // notify that the changes are over (i.e. to avoid dead locks)
        region_changed_signal.emit(region);
        // show error message
        Glib::ustring txt = "Could not add dimension: " + e.Message;
        Gtk::MessageDialog msg(*this, txt, false, Gtk::MESSAGE_ERROR);
        msg.run();
    }
}

void DimensionManager::removeDimension() {
    Glib::RefPtr<Gtk::TreeSelection> sel = treeView.get_selection();
    Gtk::TreeModel::iterator it = sel->get_selected();
    if (it) {
        try {
            // notify everybody that we're going to update the region
            region_to_be_changed_signal.emit(region);
            // remove selected dimension
            Gtk::TreeModel::Row row = *it;
            gig::dimension_def_t* dim = row[tableModel.m_definition];
            region->DeleteDimension(dim);
            // let everybody know there was a change
            region_changed_signal.emit(region);
            // update all GUI elements
            refreshManager();
        } catch (RIFF::Exception e) {
            // notify that the changes are over (i.e. to avoid dead locks)
            region_changed_signal.emit(region);
            // show error message
            Glib::ustring txt = "Could not remove dimension: " + e.Message;
            Gtk::MessageDialog msg(*this, txt, false, Gtk::MESSAGE_ERROR);
            msg.run();
        }
    }
}
